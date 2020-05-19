#include "Helper.h"

sf::Color Helper::stringToColor(std::string s) {
  if (s.compare("black") == 0)
    return sf::Color::Black;
  else if (s.compare("white") == 0)
    return sf::Color::White;
  else if (s.compare("red") == 0)
    return sf::Color::Red;
  else if (s.compare("green") == 0)
    return sf::Color::Green;
  else if (s.compare("blue") == 0)
    return sf::Color::Blue;
  else if (s.compare("yellow") == 0)
    return sf::Color::Yellow;
  else if (s.compare("magenta") == 0)
    return sf::Color::Magenta;
  else if (s.compare("cyan") == 0)
    return sf::Color::Cyan;
  else if (s.compare("orange") == 0)
    return sf::Color(255, 140, 0);
  // RGB code
  else if (s[0] == '(' && s[s.size() - 1] == ')') {
    std::stringstream ss(s.substr(1, s.length() - 2));
    std::vector<std::string> rgb;
    std::string tmp;
    while (std::getline(ss, tmp, ',')) {
      rgb.push_back(tmp);
    }

    uint8_t rgb_int[3];
    if (rgb.size() == 3) {
      try {
        for (int i = 0; i < 3; i++) {
          rgb_int[i] = std::stoi(rgb[i].c_str());
        }
      } catch (std::invalid_argument) {
        throw NoColorException();
      } catch (std::out_of_range) {
        throw NoColorException();
      }
      return sf::Color(rgb_int[0], rgb_int[1], rgb_int[2]);
    }
  }

  // Otherwise
  throw NoColorException();
}
