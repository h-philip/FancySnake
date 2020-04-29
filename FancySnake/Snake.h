#pragma once

#include <SFML/Graphics.hpp>

#include "SnakeSegment.h"
#include "Helper.h"

class Snake {
 public:
  SnakeSegment *head, *end;

  Snake(const sf::Vector2f& position,
        std::map<std::string, std::string>& settings, int length = 1);
  ~Snake();

  bool update(sf::Time time);

  void draw(sf::RenderTarget& target) const;

  void setDir(const sf::Vector2f& dir);

 private:
  sf::Vector2f direction = sf::Vector2f(1, 0);
  sf::Font font;
};
