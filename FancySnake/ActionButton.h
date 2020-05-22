#pragma once
#include "MenuButton.h"

class Menu;

class ActionButton : public MenuButton {
 public:
  ActionButton(const sf::FloatRect& rect, std::string text,
               const sf::Font& font, Menu* menu, uint8_t action);

  virtual void doAction() override;

 private:
  Menu* menu = nullptr;
  uint8_t action = 0;
};
