#include "CookieManager.h"

CookieManager::CookieManager(const sf::FloatRect& spawn_area)
    : cookie(SnakeSegment::DEFAULT_SIZE), spawn_area(spawn_area) {
  srand((unsigned int)time(NULL));
  cookie.setFillColor(DEFAULT_COLOR);

  cookie.setOrigin(SnakeSegment::DEFAULT_SIZE * .5f);
  respawnCookie();
}

bool CookieManager::update(Snake& snake) {
  if (snake.head->getGlobalBounds().intersects(cookie.getGlobalBounds())) {
    // Add body to snake
    SnakeSegment* new_segment = new SnakeSegment(snake.end);
    snake.end->next = new_segment;
    snake.end = new_segment;

    respawnCookie();
    return true;
  }

  return false;
}

void CookieManager::draw(sf::RenderTarget& target) { target.draw(cookie); }

void CookieManager::respawnCookie() {
  sf::Vector2f pos(spawn_area.left, spawn_area.top);
  pos += SnakeSegment::DEFAULT_SIZE * .5f;
  pos.x +=
      (float)(rand() % (int)(spawn_area.width - SnakeSegment::DEFAULT_SIZE.x));
  pos.y +=
      (float)(rand() % (int)(spawn_area.height - SnakeSegment::DEFAULT_SIZE.y));

  cookie.setPosition(pos);
}
