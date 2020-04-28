#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <thread>

#include "CookieManager.h"
#include "Snake.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(900, 900), "Nuttööö");

  sf::Vector2f start_pos = window.getView().getCenter();
  Snake snake(start_pos);
  const float BORDER_WIDTH = 20.f;
  CookieManager cm(sf::FloatRect(BORDER_WIDTH, BORDER_WIDTH,
                                 window.getSize().x - BORDER_WIDTH * 2.f,
                                 window.getSize().y - BORDER_WIDTH * 2.f));

  bool game_over = false;

  sf::Clock update_clock;
  while (window.isOpen()) {
    // Events
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;

        case sf::Event::KeyPressed:
          switch (event.key.code) {
            // Exit
            case sf::Keyboard::Escape:
              window.close();
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
              snake.setDir(sf::Vector2f(0, -1));
              break;

            case sf::Keyboard::A:
            case sf::Keyboard::Left:
              snake.setDir(sf::Vector2f(-1, 0));
              break;

            case sf::Keyboard::D:
            case sf::Keyboard::Right:
              snake.setDir(sf::Vector2f(1, 0));
              break;

            case sf::Keyboard::S:
            case sf::Keyboard::Down:
              snake.setDir(sf::Vector2f(0, 1));
              break;
          }
      }
    }

    // Time
    if (update_clock.getElapsedTime().asMilliseconds() < 50)
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    sf::Time time = update_clock.restart();
    if (time.asSeconds() > 1) time = sf::seconds(1);

    // Updates

    game_over |= !snake.update(time);
    cm.update(snake);

    // Check for hitting borders
    const sf::FloatRect& head = snake.head->getGlobalBounds();
    if (head.left < 0 ||
        head.left + SnakeSegment::DEFAULT_SIZE.x > window.getSize().x ||
        head.top < 0 ||
        head.top + SnakeSegment::DEFAULT_SIZE.y > window.getSize().y) {
      game_over |= true;
    }

    // Check for game_over
    if (game_over) {
      std::cout << "Game Over!" << std::endl;
      window.close();
      continue;
    }

    // Draws
    window.clear(sf::Color::White);
    snake.draw(window);
    cm.draw(window);
    window.display();
  }
}