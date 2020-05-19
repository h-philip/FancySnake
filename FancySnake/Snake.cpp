#include "Snake.h"

Snake::Snake(const sf::Vector2f& position, Settings& settings, int length,
             bool second) {
  // Settings
  SnakeSegment::speed = settings.snake_speed;
  SnakeSegment::size.y = (SnakeSegment::size.x = (float)settings.snake_size);

  if (second) {
    // Second snake (multiplayer)
    color_body = settings.color_snake_body_2;
    color_head = settings.color_snake_head_2;
  } else {
    // Main snake
    color_body = settings.color_snake_body;
    color_head = settings.color_snake_head;
  }

  head = new SnakeSegment(nullptr, color_head, color_body);
  head->setPosition(position);
  end = head;
  for (int i = 0; i < length; i++) {
    SnakeSegment* tmp = new SnakeSegment(end, color_head, color_body);
    end->next = tmp;
    end = tmp;
  }

  // Because size might change after definition
  SnakeSegment::body_distance = SnakeSegment::size.x * 1.f;
}

Snake::~Snake() {
  SnakeSegment* seg = head;
  while (seg) {
    SnakeSegment* tmp = seg;
    seg = seg->next;
    delete tmp;
  }
}

bool Snake::update(sf::Time time) {
  bool ret = true;

  SnakeSegment* seg = head;
  while (seg) {
    if (seg->prev == nullptr) {
      // Head
      ret = seg->update(time, direction);
    } else {
      // Body
      seg->update(time);
    }
    seg = seg->next;
  }

  return ret;
}

void Snake::draw(sf::RenderTarget& target) const {
  SnakeSegment* seg = head;
  while (seg) {
    seg->draw(target);
    seg = seg->next;
  }
}

void Snake::setDir(const sf::Vector2f& dir) {
  // Prevent unnecessary goto_points
  if (direction == dir) return;
  // 180° turn not allowed
  if (direction * -1.f == dir) return;

  direction = dir;
  if (head->next)
    head->next->goto_points.push(new sf::Vector2f(head->getPosition()));
}
