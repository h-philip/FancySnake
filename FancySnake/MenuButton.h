#pragma once

#include <SFML/Graphics.hpp>

class MenuButton {
 public:
  sf::Text text;
  sf::RectangleShape rect;

  void update(const sf::Vector2f& mouse_pos, bool mouse_pressed);

  virtual void doAction() = 0;

  void draw(sf::RenderTarget& target) const;

 protected:
  MenuButton(const sf::FloatRect& rect, std::string text, const sf::Font& font);
};
