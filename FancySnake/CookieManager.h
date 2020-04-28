#pragma once

#include <SFML/Graphics.hpp>

#include "Snake.h"

class CookieManager {
 public:
  const sf::Color DEFAULT_COLOR = sf::Color::Magenta;

  CookieManager(const sf::FloatRect& spawn_area);

  bool update(Snake& snake);

  void draw(sf::RenderTarget& target);

 private:
  void respawnCookie();

  sf::FloatRect spawn_area;
  sf::RectangleShape cookie;
};
