#include "SettingsButton.h"

SettingsButton::SettingsButton(const sf::FloatRect& rect, std::string text,
                               const sf::Font& font, sf::Color* settings_value,
                               std::vector<Settings::color_p>& colors)
    : MenuButton(rect, text, font),
      colors(colors),
      min(0),
      max(0),
      step(0),
      start(text) {
  type = Type::Color;
  current_color = settings_value;
  colors_it = colors.begin();
  while (colors_it->second != *current_color) {
    colors_it++;
    if (colors_it == colors.end()) {
      throw "Color not found in vector!";
    }
  }
  this->text.setString(start + colors_it->first);
  this->text.setOrigin(this->text.getGlobalBounds().width * .5f,
                       this->text.getGlobalBounds().height * .5f);
}

SettingsButton::SettingsButton(const sf::FloatRect& rect, std::string text,
                               const sf::Font& font, int* settings_value,
                               int min, int max, int step)
    : MenuButton(rect, text, font),
      min(min),
      max(max),
      step(step),
      start(text) {
  type = Type::Int;
  current_int = settings_value;

  this->text.setString(start + std::to_string(*current_int));
  this->text.setOrigin(this->text.getGlobalBounds().width * .5f,
                       this->text.getGlobalBounds().height * .5f);
}

void SettingsButton::doAction() {
  switch (type) {
    case Type::Color:
      colors_it++;
      if (colors_it == colors.end()) colors_it = colors.begin();
      current_color = &colors_it->second;
      this->text.setString(start + colors_it->first);
      break;

    case Type::Int:
      *current_int += step;
      if (*current_int > max)
        *current_int = min;
      else if (*current_int < min)
        *current_int = max;
      this->text.setString(start + std::to_string(*current_int));
      break;
  }
  this->text.setOrigin(this->text.getGlobalBounds().width * .5f,
                       this->text.getGlobalBounds().height * .5f);
}
