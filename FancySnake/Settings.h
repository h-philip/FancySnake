#pragma once

#include <SFML/Graphics.hpp>

#include "ConfigParser.h"
#include "Helper.h"

class Settings {
 public:
  //// Default Values
  // Colors
  static const sf::Color DEFAULT_COLOR_BACKGROUND;
  static const sf::Color DEFAULT_COLOR_COOKIE;
  static const sf::Color DEFAULT_COLOR_SNAKE_BODY;
  static const sf::Color DEFAULT_COLOR_SNAKE_HEAD;
  static const sf::Color DEFAULT_COLOR_SNAKE_BODY_2;
  static const sf::Color DEFAULT_COLOR_SNAKE_HEAD_2;

  // Window size
  static const int DEFAULT_WINDOW_WIDTH;
  static const int DEFAULT_WINDOW_HEIGHT;

  // Snake
  static const sf::Time DEFAULT_SNAKE_SPEED;
  static const int DEFAULT_SNAKE_SIZE;
  static const int DEFAULT_SNAKE_BODY_DISTANCE;

  //// Constructor
  Settings(std::string file);

  //// Values
  // Colors
  sf::Color color_background = DEFAULT_COLOR_BACKGROUND;
  sf::Color color_cookie = DEFAULT_COLOR_COOKIE;
  sf::Color color_snake_body = DEFAULT_COLOR_SNAKE_BODY;
  sf::Color color_snake_head = DEFAULT_COLOR_SNAKE_HEAD;
  sf::Color color_snake_body_2 = DEFAULT_COLOR_SNAKE_BODY_2;
  sf::Color color_snake_head_2 = DEFAULT_COLOR_SNAKE_HEAD_2;

  // Window size
  int window_width = DEFAULT_WINDOW_WIDTH;
  int window_height = DEFAULT_WINDOW_HEIGHT;

  // Snake
  sf::Time snake_speed = DEFAULT_SNAKE_SPEED;
  int snake_size = DEFAULT_SNAKE_SIZE;
};
