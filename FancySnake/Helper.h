#pragma once
#include <SFML/Graphics.hpp>
#include <exception>
#include <sstream>

class NoColorException : public std::exception {};

class Helper {
 public:
  static sf::Color stringToColor(std::string s);
};
