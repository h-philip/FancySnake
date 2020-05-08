#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <thread>

#include "ConfigParser.h"
#include "CookieManager.h"
#include "Helper.h"
#include "Menu.h"
#include "Snake.h"

int main() {
  // Settings
  std::map<std::string, std::string> settings =
      ConfigParser::parse("settings.txt");
  sf::Color background_color = sf::Color::White;
  if (settings.find("color-background") != settings.end()) {
    sf::Color tmp = Helper::stringToColor(settings["color-background"]);
    if (tmp.r != 1) background_color = tmp;
  }

  // Window
  int width = 900, height = 900;
  if (settings.find("window-width") != settings.end())
    width = atoi(settings["window-width"].c_str());
  if (settings.find("window-height") != settings.end())
    height = atoi(settings["window-height"].c_str());
  sf::RenderWindow window(sf::VideoMode(width, height), "Nuttööö");

  // Menu
  Menu menu(window.getSize());
  Menu::State last_menu_state = menu.state;

  // Snake and Cookies
  sf::Vector2f start_pos = window.getView().getCenter();
  Snake* snake = new Snake(start_pos, settings);
  const float BORDER_WIDTH = 20.f;
  CookieManager cm(sf::FloatRect(BORDER_WIDTH, BORDER_WIDTH,
                                 window.getSize().x - BORDER_WIDTH * 2.f,
                                 window.getSize().y - BORDER_WIDTH * 2.f),
                   settings);

  bool game_over = false;
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
            // Exit
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
            case sf::Keyboard::Up:
              snake->setDir(sf::Vector2f(0, -1));
              break;

            case sf::Keyboard::A:
            case sf::Keyboard::Left:
              snake->setDir(sf::Vector2f(-1, 0));
              break;

            case sf::Keyboard::D:
            case sf::Keyboard::Right:
              snake->setDir(sf::Vector2f(1, 0));
              break;

            case sf::Keyboard::S:
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
        cm.respawnCookie();
      }
    }

    // Time
    if (update_clock.getElapsedTime().asMilliseconds() < 50)
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    sf::Time time = update_clock.restart();
    if (time.asSeconds() > 1) time = sf::seconds(1);

    // Updates
    if (menu.state == Menu::State::InGame) {
      game_over |= !snake->update(time);
      cm.update(snake);

      // Check for hitting borders
      const sf::FloatRect& head = snake->head->getGlobalBounds();
      if (head.left < 0 ||
          head.left + SnakeSegment::size.x > window.getSize().x ||
          head.top < 0 ||
          head.top + SnakeSegment::size.y > window.getSize().y) {
        game_over |= true;
      }
    } else if (menu.state == Menu::State::Exit)
      window.close();

    // Check for game_over
    if (game_over) {
      menu.state = Menu::State::GameOver;
      game_over = false;
    }

    // Draws
    window.clear(background_color);
    if (menu.state == Menu::State::InGame ||
        menu.state == Menu::State::InGameMenu ||
        menu.state == Menu::State::GameOver) {
      snake->draw(window);
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