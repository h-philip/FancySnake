#include "ActionButton.h"

#include "Menu.h"

ActionButton::ActionButton(const sf::FloatRect& rect, std::string text,
                       const sf::Font& font, Menu* menu, uint8_t action)
    : MenuButton(rect, text, font) {
  this->menu = menu;
  this->action = action;
}

void ActionButton::doAction() { this->menu->doAction(this->action); }
