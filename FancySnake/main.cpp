#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <thread>

#include "CookieManager.h"
#include "Menu.h"
#include "Settings.h"
#include "Snake.h"

int main() {
  // Settings
  Settings settings("settings.txt");
  sf::Color& background_color = settings.color_background;

  // Window
  sf::RenderWindow window(
      sf::VideoMode(settings.window_width, settings.window_height), "Nutt���");

  // Menu
  Menu menu(window.getSize(), settings);
  Menu::State last_menu_state = menu.state;

  // Snake and Cookies
  sf::Vector2f start_pos = window.getView().getCenter();
  Snake* snake = new Snake(start_pos, settings);
  Snake* lm_snake = nullptr;  // Local multiplayer snake
  const float BORDER_WIDTH = 20.f;
  CookieManager cm(sf::FloatRect(BORDER_WIDTH, BORDER_WIDTH,
                                 window.getSize().x - BORDER_WIDTH * 2.f,
                                 window.getSize().y - BORDER_WIDTH * 2.f),
                   settings);

  bool game_over = false;
  bool lm_game_over = false;
  bool simple_bot_mode = false;
  sf::Clock update_clock;
  while (window.isOpen()) {
    // Events
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        //// Menu
        case sf::Event::MouseMoved:
          menu.update(window.mapPixelToCoords(
                          sf::Vector2i(event.mouseMove.x, event.mouseMove.y)),
                      false);
          break;

        case sf::Event::MouseButtonReleased:
          menu.update(window.mapPixelToCoords(sf::Vector2i(
                          event.mouseButton.x, event.mouseButton.y)),
                      true);
          break;

        case sf::Event::Closed:
          window.close();
          break;

        case sf::Event::KeyPressed:
          switch (event.key.code) {
            // Escape
            case sf::Keyboard::Escape:
              if (menu.state == Menu::State::InGame)
                menu.state = Menu::State::InGameMenu;
              else if (menu.state == Menu::State::InGameMenu)
                menu.state = Menu::State::InGame;

              break;

              // Go faster
            case sf::Keyboard::Add:
              if (SnakeSegment::speed.asMicroseconds() > 500)
                SnakeSegment::speed -= sf::microseconds(500);
              else if (SnakeSegment::speed.asMicroseconds() > 50)
                SnakeSegment::speed -= sf::microseconds(50);
              break;

              // Go slower
            case sf::Keyboard::Subtract:
              SnakeSegment::speed += sf::microseconds(1000);
              break;

              //// Directions
            case sf::Keyboard::W:
              if (lm_snake) {
                lm_snake->setDir(sf::Vector2f(0, -1));
                break;
              }  // Do not break after this
            case sf::Keyboard::Up:
              snake->setDir(sf::Vector2f(0, -1));
              break;

            case sf::Keyboard::A:
              if (lm_snake) {
                lm_snake->setDir(sf::Vector2f(-1, 0));
                break;
              }  // Do not break after this
            case sf::Keyboard::Left:
              snake->setDir(sf::Vector2f(-1, 0));
              break;

            case sf::Keyboard::D:
              if (lm_snake) {
                lm_snake->setDir(sf::Vector2f(1, 0));
                break;
              }  // Do not break after this
            case sf::Keyboard::Right:
              snake->setDir(sf::Vector2f(1, 0));
              break;

            case sf::Keyboard::S:
              if (lm_snake) {
                lm_snake->setDir(sf::Vector2f(0, 1));
                break;
              }  // Do not break after this
            case sf::Keyboard::Down:
              snake->setDir(sf::Vector2f(0, 1));
              break;
          }
      }
    }

    // Reset snake if new game
    if (menu.state == Menu::State::InGame) {
      if (last_menu_state == Menu::State::MainMenu) {
        delete snake;
        snake = new Snake(start_pos, settings);

        if (lm_snake) delete lm_snake;
        // Multiplayer
        if (menu.isLocalMultiplayer()) {
          lm_snake =
              new Snake(start_pos - sf::Vector2f(0, SnakeSegment::size.x * 2.f),
                        settings, 1, true);
          lm_snake->head->second_head = snake->head;
          snake->head->second_head = lm_snake->head;
        } else {
          lm_snake = nullptr;
        }

        cm = CookieManager(
            sf::FloatRect(BORDER_WIDTH, BORDER_WIDTH,
                          window.getSize().x - BORDER_WIDTH * 2.f,
                          window.getSize().y - BORDER_WIDTH * 2.f),
            settings);
      }
    }

    // Time
    if (update_clock.getElapsedTime().asMilliseconds() < 50)
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    sf::Time time = update_clock.restart();
    if (time.asSeconds() > 1) time = sf::seconds(1);

    // Updates
    if (menu.state == Menu::State::InGame) {
      if (simple_bot_mode) {
        // Bot enabled
        const sf::Vector2f &s_pos = snake->head->getPosition(),
                           &c_pos = cm.getPosition();
        if (s_pos.x < c_pos.x - .5 * settings.snake_size)
          snake->setDir(sf::Vector2f(1, 0));
        else if (s_pos.x > c_pos.x + .5 * settings.snake_size)
          snake->setDir(sf::Vector2f(-1, 0));
        if (s_pos.y < c_pos.y - .5 * settings.snake_size)
          snake->setDir(sf::Vector2f(0, 1));
        else if (s_pos.y > c_pos.y + .5 * settings.snake_size)
          snake->setDir(sf::Vector2f(0, -1));
      }
      game_over |= !snake->update(time);
      if (lm_snake) lm_game_over |= !lm_snake->update(time);
      cm.update(snake);
      if (lm_snake) cm.update(lm_snake);

      // Check for hitting borders
      const sf::FloatRect& head = snake->head->getGlobalBounds();
      if (head.left < 0 ||
          head.left + SnakeSegment::size.x > window.getSize().x ||
          head.top < 0 ||
          head.top + SnakeSegment::size.y > window.getSize().y) {
        game_over |= true;
      }
      // 2nd snake
      if (lm_snake) {
        const sf::FloatRect& lm_head = lm_snake->head->getGlobalBounds();
        if (lm_head.left < 0 ||
            lm_head.left + SnakeSegment::size.x > window.getSize().x ||
            lm_head.top < 0 ||
            lm_head.top + SnakeSegment::size.y > window.getSize().y) {
          lm_game_over |= true;
        }
      }
    } else if (menu.state == Menu::State::Exit)
      window.close();

    // Check for game_over // TODO difference
    if (game_over) {
      menu.state = Menu::State::GameOver;
      game_over = false;
      lm_game_over = false;
    } else if (lm_snake && lm_game_over) {
      menu.state = Menu::State::GameOver;
      game_over = false;
      lm_game_over = false;
    }

    // Draws
    window.clear(background_color);
    if (menu.state == Menu::State::InGame ||
        menu.state == Menu::State::InGameMenu ||
        menu.state == Menu::State::GameOver) {
      snake->draw(window);
      if (lm_snake) lm_snake->draw(window);
      cm.draw(window);
    }
    if (menu.state != Menu::State::InGame) menu.draw(window);
    window.display();

    // Menu state
    last_menu_state = menu.state;
  }

  // Delete
  delete snake;
}