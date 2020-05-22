#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Snake.h"

class CookieManager {
 public:
  static const std::string AUDIO_DIR;
  static const std::string AUDIO_FILE_PREFIX;
  static const std::string AUDIO_FILE_SUFFIX;
  static const int FILES_AMOUNT = 15;

  sf::Color color = sf::Color::Cyan;

  CookieManager(const sf::FloatRect& spawn_area,
                Settings& settings);

  bool update(Snake* snake);

  void draw(sf::RenderTarget& target);

  void respawnCookie();

  const sf::Vector2f& getPosition();

 private:
  sf::FloatRect spawn_area;
  sf::RectangleShape cookie;
  sf::SoundBuffer audio_buffers[FILES_AMOUNT];
  sf::Sound sound;
};
