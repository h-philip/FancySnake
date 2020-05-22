#include "MenuButton.h"

void MenuButton::update(const sf::Vector2f& mouse_pos, bool mouse_pressed) {
  if (rect.getGlobalBounds().intersects(
          sf::FloatRect(mouse_pos.x, mouse_pos.y, 1, 1))) {
    this->rect.setFillColor(sf::Color(200, 200, 200));

    // If clicked, trigger function
    if (mouse_pressed) {
        doAction();
    }
  } else {
    this->rect.setFillColor(sf::Color(100, 100, 100));
  }
}

void MenuButton::draw(sf::RenderTarget& target) const {
  target.draw(rect);
  target.draw(text);
}

MenuButton::MenuButton(const sf::FloatRect& rect, std::string text,
                       const sf::Font& font)
    : rect(sf::Vector2f(rect.width, rect.height)), text(text, font) {
  this->rect.setFillColor(sf::Color(100, 100, 100));
  this->rect.setOrigin(rect.width * .5f, rect.height * .5f);
  this->rect.setPosition(rect.left, rect.top);

  this->text.setFont(font);
  this->text.setString(text);
  this->text.setOrigin(this->text.getGlobalBounds().width * .5f,
                       this->text.getGlobalBounds().height * .5f);
  this->text.setPosition(rect.left, rect.top);
}
