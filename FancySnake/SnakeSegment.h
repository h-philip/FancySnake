#pragma once

#include <SFML/Graphics.hpp>
#include <queue>

#include "Settings.h"

class SnakeSegment : public sf::RectangleShape {
 public:
  const sf::Color& body_color;
  const sf::Color& head_color;
  static float body_distance;

  // Speed in Time / point
  static sf::Vector2f size;
  static sf::Time speed;

  std::queue<sf::Vector2f*> goto_points;
  SnakeSegment *next = nullptr, *prev;

  SnakeSegment* second_head = nullptr;  // Head of other (multiplayer) snake

  SnakeSegment(SnakeSegment* prev, const sf::Color& head_color,
               const sf::Color& body_color);
  ~SnakeSegment();

  bool update(sf::Time time);

  bool update(sf::Time time, const sf::Vector2f& direction);

  void draw(sf::RenderTarget& target) const;

 private:
  sf::Text text;
};
