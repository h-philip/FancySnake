#include "Helper.h"

sf::Color Helper::stringToColor(std::string s) {
  if (s.compare("Black") == 0)
    return sf::Color::Black;
  else if (s.compare("White") == 0)
    return sf::Color::White;
  else if (s.compare("Red") == 0)
    return sf::Color::Red;
  else if (s.compare("Green") == 0)
    return sf::Color::Green;
  else if (s.compare("Blue") == 0)
    return sf::Color::Blue;
  else if (s.compare("Yellow") == 0)
    return sf::Color::Yellow;
  else if (s.compare("Magenta") == 0)
    return sf::Color::Magenta;
  else if (s.compare("Cyan") == 0)
    return sf::Color::Cyan;
  else
    return sf::Color(1, 0, 0);
}
