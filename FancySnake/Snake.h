#pragma once

#include <SFML/Graphics.hpp>

#include "Helper.h"
#include "Settings.h"
#include "SnakeSegment.h"

class Snake {
 public:
  SnakeSegment *head, *end;

  sf::Color color_head, color_body;

  Snake(const sf::Vector2f& position, Settings& settings, int length = 1,
        bool second = false);
  ~Snake();

  bool update(sf::Time time);

  void draw(sf::RenderTarget& target) const;

  void setDir(const sf::Vector2f& dir);

 private:
  sf::Vector2f direction = sf::Vector2f(1, 0);
  sf::Font font;
};
