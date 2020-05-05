#pragma once

#include <SFML/Graphics.hpp>
class Menu;

class MenuButton {
 public:
  sf::Text text;
  sf::RectangleShape rect;

  MenuButton();

  MenuButton(const sf::FloatRect& rect, std::string text, const sf ::Font& font,
             Menu* menu, uint8_t action);

  void update(const sf::Vector2f& mouse_pos, bool mouse_pressed);

  void draw(sf::RenderTarget& target) const;

 private:
  Menu* menu;
  uint8_t action;
};
