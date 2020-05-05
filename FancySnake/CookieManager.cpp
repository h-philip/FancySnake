#include "CookieManager.h"

const std::string CookieManager::AUDIO_DIR = "Audio/";
const std::string CookieManager::AUDIO_FILE_PREFIX = "Nutt";

const std::string CookieManager::AUDIO_FILE_SUFFIX = ".wav";

CookieManager::CookieManager(const sf::FloatRect& spawn_area,
                             std::map<std::string, std::string>& settings)
    : cookie(SnakeSegment::size), spawn_area(spawn_area) {
  // Settings
  if (settings.find("color-cookie") != settings.end()) {
    sf::Color tmp = Helper::stringToColor(settings["color-cookie"]);
    if (tmp.r != 1) color = tmp;
  }

  // Cookie
  srand((unsigned int)time(NULL));
  cookie.setFillColor(color);

  cookie.setOrigin(SnakeSegment::size * .5f);
  respawnCookie();

  // Load audios
  for (int i = 0; i < FILES_AMOUNT; i++) {
    audio_buffers[i] = sf::SoundBuffer();
    audio_buffers[i].loadFromFile(AUDIO_DIR + AUDIO_FILE_PREFIX +
                                  std::to_string(i + 1) + AUDIO_FILE_SUFFIX);
  }

  srand((int)time(NULL));
}

bool CookieManager::update(Snake* snake) {
  if (snake->head->getGlobalBounds().intersects(cookie.getGlobalBounds())) {
    // Add body to snake
    SnakeSegment* new_segment = new SnakeSegment(snake->end);
    snake->end->next = new_segment;
    snake->end = new_segment;

    // Sound
    int index = rand() % FILES_AMOUNT;
    sound.setBuffer(audio_buffers[index]);
    sound.play();

    // Respawn cookie
    respawnCookie();
    return true;
  }

  return false;
}

void CookieManager::draw(sf::RenderTarget& target) { target.draw(cookie); }

void CookieManager::respawnCookie() {
  // TODO: Don't spawn inside snake
  
  sf::Vector2f pos(spawn_area.left, spawn_area.top);
  pos += SnakeSegment::size * .5f;
  pos.x += (float)(rand() % (int)(spawn_area.width - SnakeSegment::size.x));
  pos.y += (float)(rand() % (int)(spawn_area.height - SnakeSegment::size.y));

  cookie.setPosition(pos);
}
