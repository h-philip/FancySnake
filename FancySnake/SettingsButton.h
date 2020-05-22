#pragma once
#include "MenuButton.h"
#include "Settings.h"

class SettingsButton : public MenuButton {
 public:
  enum class Type { Color, Int };

  SettingsButton(const sf::FloatRect& rect, std::string text,
                 const sf::Font& font, sf::Color* settings_value,
                 std::vector<Settings::color_p>& colors);

  SettingsButton(const sf::FloatRect& rect, std::string text,
                 const sf::Font& font, int* settings_value, int min, int max,
                 int step);

  virtual void doAction() override;

  Type type;
  std::string start;

  sf::Color* current_color = nullptr;
  int* current_int = nullptr;

  int min, max, step;
  std::vector<Settings::color_p> empty_colors;  // Do not use
  std::vector<Settings::color_p>& colors = empty_colors;
  std::vector<Settings::color_p>::iterator colors_it;
};
