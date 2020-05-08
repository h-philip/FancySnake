#include "SnakeSegment.h"

#include <iostream>

sf::Color SnakeSegment::body_color = sf::Color::Magenta;
sf::Color SnakeSegment::head_color = sf::Color::Blue;
float SnakeSegment::body_distance = 0;
sf::Vector2f SnakeSegment::size = sf::Vector2f(20, 20);
sf::Time SnakeSegment::speed = sf::milliseconds(5);

SnakeSegment::SnakeSegment(SnakeSegment* prev) : prev(prev) {
  if (prev == nullptr)  // Head
    setFillColor(head_color);
  else  // Body
    setFillColor(body_color);
  setSize(size);
  setOrigin(size * .5f);

  if (prev) setPosition(prev->getPosition());

  // TODO text
}

SnakeSegment::~SnakeSegment() {
  while (!goto_points.empty()) {
    delete goto_points.front();
    goto_points.pop();
  }
}

bool SnakeSegment::update(sf::Time time) {
  // get direction towards next element
  sf::Vector2f dir;
  if (!goto_points.empty()) {
    dir = *(goto_points.front()) - getPosition();
  } else {
    dir = prev->getPosition() - getPosition();
    if (sqrt(pow(dir.x, 2) + pow(dir.y, 2)) <= body_distance + .0001f)
      return true;
  }

  return update(time, dir);
}

bool SnakeSegment::update(sf::Time time, const sf::Vector2f& direction) {
  if (time.asMicroseconds() == 0 || (direction.x == 0 && direction.y == 0)) {
    if (!goto_points.empty()) {
      delete goto_points.front();
      goto_points.pop();
      update(time);
    }
    return true;
  }

  // points to go
  float points =
      (float)((double)time.asMicroseconds() / (double)speed.asMicroseconds());

  // Create normalized direction
  float length = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
  sf::Vector2f n_dir = direction / length;

  // The path to go
  float path = !goto_points.empty() ? fminf(length, points)
                                    : (prev ? length - body_distance : points);

  // Move
  move(path * n_dir);
  text.move(path * n_dir);

  // Calculate whether time was fully used
  float points_left = points - path;
  if (!goto_points.empty() && points_left >= 0 && length <= points) {
    if (next)
      next->goto_points.push(goto_points.front());
    else
      delete goto_points.front();
    goto_points.pop();
  }
  // Time left -> update again
  if (points_left > 0) update(speed * points_left);

  // Head and next exists and 2nd next exists
  // This is to prevent check with next two elements
  else if (prev == nullptr && next && next->next) {
    // Check if collision with bodies
    SnakeSegment* seg = next->next->next;
    while (seg) {
      if (getGlobalBounds().intersects(seg->getGlobalBounds())) {
        // Snake collides with own body
        // -> Double check with another body part
        // This is to prevent instant death when spawning with multiple body
        // parts
        if (!next->getGlobalBounds().intersects(seg->getGlobalBounds()))
          return false;
      }
      seg = seg->next;
    }
  }
  // 2nd snake
  if (second_head) {
    SnakeSegment* seg = second_head;
    while (seg) {
      if (getGlobalBounds().intersects(seg->getGlobalBounds())) {
        // Snake collides with other snake
        return false;
      }
      seg = seg->next;
    }
  }
  return true;
}

void SnakeSegment::draw(sf::RenderTarget& target) const {
  target.draw(*this);
  target.draw(text);
}
