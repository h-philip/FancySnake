#pragma once

#include <SFML/Graphics.hpp>
#include <queue>

class SnakeSegment : public sf::RectangleShape {
 public:
  static const sf::Vector2f DEFAULT_SIZE;
  static const sf::Color DEFAULT_COLOR;
  static const sf::Color DEFAULT_HEAD_COLOR;
  static const float BODY_DISTANCE;

  // Speed in Time / point
  static sf::Time speed;

  std::queue<sf::Vector2f*> goto_points;
  SnakeSegment *next = nullptr, *prev;

  SnakeSegment(SnakeSegment* prev);
  ~SnakeSegment();

  bool update(sf::Time time);

  bool update(sf::Time time, const sf::Vector2f& direction);

  void draw(sf::RenderTarget& target) const;

 private:
  sf::Text text;
};
