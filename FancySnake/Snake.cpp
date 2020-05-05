#include "Snake.h"

Snake::Snake(const sf::Vector2f& position,
             std::map<std::string, std::string>& settings, int length) {
  // Settings
  if (settings.find("snake-speed") != settings.end()) {
    SnakeSegment::speed =
        sf::milliseconds(atoi(settings["snake-speed"].c_str()));
  }
  if (settings.find("snake-size") != settings.end()) {
    SnakeSegment::size.y =
        (SnakeSegment::size.x = (float)atoi(settings["snake-size"].c_str()));
  }
  if (settings.find("color-head") != settings.end()) {
    sf::Color tmp = Helper::stringToColor(settings["color-head"]);
    if (tmp.r != 1) SnakeSegment::head_color = tmp;
  }
  if (settings.find("color-body") != settings.end()) {
    sf::Color tmp = Helper::stringToColor(settings["color-body"]);
    if (tmp.r != 1) SnakeSegment::body_color = tmp;
  }

  head = new SnakeSegment(nullptr);
  head->setPosition(position);
  end = head;
  for (int i = 0; i < length; i++) {
    SnakeSegment* tmp = new SnakeSegment(end);
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
