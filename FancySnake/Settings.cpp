#include "Settings.h"

std::vector<Settings::color_p> Settings::valid_colors;

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

  //// Colors
  typedef std::map<sf::Color*, std::string> color_map;
  typedef std::pair<sf::Color*, std::string> color_pair;
  color_map color_values;
  color_values.insert(color_pair(&color_background, "color-background"));
  color_values.insert(color_pair(&color_cookie, "color-cookie"));
  color_values.insert(color_pair(&color_snake_body, "color-snake-body"));
  color_values.insert(color_pair(&color_snake_head, "color-snake-head"));
  color_values.insert(color_pair(&color_snake_body_2, "color-snake-body-2"));
  color_values.insert(color_pair(&color_snake_head_2, "color-snake-head-2"));
  for (auto& pair : color_values) {
    if (config.find(pair.second) != config.end()) {
      try {
        *pair.first = Helper::stringToColor(config[pair.second]);
      } catch (NoColorException) {
      }
    }
  }

  //// Numbers
  typedef std::map<int*, std::string> int_map;
  typedef std::pair<int*, std::string> int_pair;
  int_map int_values;
  // Window
  int_values.insert(int_pair(&window_width, "window-width"));
  int_values.insert(int_pair(&window_height, "window-height"));
  // Snake
  int_values.insert(int_pair(&snake_size, "snake-size"));

  for (auto& pair : int_values) {
    if (config.find(pair.second) != config.end()) try {
        *pair.first = std::stoi(config[pair.second].c_str());
      } catch (std::exception) {
      }
  }

  //// Other
  // Snake
  if (config.find("snake-speed") != config.end()) {
    try {
      snake_speed = sf::milliseconds(std::stoi(config["snake-speed"].c_str()));
    } catch (std::exception) {
    }
  }

  // Valid colors
  valid_colors.clear();
  valid_colors.push_back(color_p("Black", sf::Color::Black));
  valid_colors.push_back(color_p("White", sf::Color::White));
  valid_colors.push_back(color_p("Red", sf::Color::Red));
  valid_colors.push_back(color_p("Green", sf::Color::Green));
  valid_colors.push_back(color_p("Blue", sf::Color::Blue));
  valid_colors.push_back(color_p("Yellow", sf::Color::Yellow));
  valid_colors.push_back(color_p("Magenta", sf::Color::Magenta));
  valid_colors.push_back(color_p("Cyan", sf::Color::Cyan));
  valid_colors.push_back(color_p("Orange", sf::Color(255, 140, 0)));
}
