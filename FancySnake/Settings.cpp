#include "Settings.h"

// Colors
const sf::Color Settings::DEFAULT_COLOR_BACKGROUND = sf::Color::White;
const sf::Color Settings::DEFAULT_COLOR_COOKIE = sf::Color::Cyan;
const sf::Color Settings::DEFAULT_COLOR_SNAKE_BODY = sf::Color::Magenta;
const sf::Color Settings::DEFAULT_COLOR_SNAKE_HEAD = sf::Color::Blue;
const sf::Color Settings::DEFAULT_COLOR_SNAKE_BODY_2 =
    sf::Color(255, 140, 0);  // Orange
const sf::Color Settings::DEFAULT_COLOR_SNAKE_HEAD_2 = sf::Color::Red;

// Window size
const int Settings::DEFAULT_WINDOW_WIDTH = 900;
const int Settings::DEFAULT_WINDOW_HEIGHT = 900;

// Snake
const sf::Time Settings::DEFAULT_SNAKE_SPEED = sf::milliseconds(5);
const int Settings::DEFAULT_SNAKE_SIZE = 20;
const int Settings::DEFAULT_SNAKE_BODY_DISTANCE = 0;

Settings::Settings(std::string file) {
  // Parse file
  std::map<std::string, std::string> config = ConfigParser::parse(file);

  //// Set values
  // Color
  if (config.find("color-background") != config.end()) {
    try {
      color_background = Helper::stringToColor(config["color-background"]);
    } catch (NoColorException) {
    }
  }

  if (config.find("color-cookie") != config.end()) {
    try {
      color_cookie = Helper::stringToColor(config["color-cookie"]);
    } catch (NoColorException) {
    }
  }

  if (config.find("color-snake-body") != config.end()) {
    try {
      color_snake_body = Helper::stringToColor(config["color-snake-body"]);
    } catch (NoColorException) {
    }
  }

  if (config.find("color-snake-head") != config.end()) {
    try {
      color_snake_head = Helper::stringToColor(config["color-snake-head"]);
    } catch (NoColorException) {
    }
  }

  if (config.find("color-snake-body-2") != config.end()) {
    try {
      color_snake_body_2 = Helper::stringToColor(config["color-snake-body-2"]);
    } catch (NoColorException) {
    }
  }

  if (config.find("color-snake-head-2") != config.end()) {
    try {
      color_snake_head_2 = Helper::stringToColor(config["color-snake-head-2"]);
    } catch (NoColorException) {
    }
  }

  // Window
  if (config.find("window-width") != config.end()) try {
      window_width = std::stoi(config["window-width"].c_str());
    } catch (std::exception) {
    }

  if (config.find("window-height") != config.end()) try {
      window_height = std::stoi(config["window-height"].c_str());
    } catch (std::exception) {
    }

  // Snake
  if (config.find("snake-speed") != config.end()) {
    try {
      snake_speed = sf::milliseconds(std::stoi(config["snake-speed"].c_str()));
    } catch (std::exception) {
    }
  }

  if (config.find("snake-size") != config.end()) {
    try {
      snake_size = std::stoi(config["snake-size"].c_str());
    } catch (std::exception) {
    }
  }
}
