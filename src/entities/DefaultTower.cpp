#include "DefaultTower.hpp"
#include "../players/Player.hpp"
#include <stdexcept>

namespace {
  static constexpr int HEALTH = 10000;
  static constexpr int DAMAGE = 50;
  static constexpr float ATTACK_COOLDOWN = 1.5f;
  static constexpr float ATTACK_RANGE = 100.f;
  static constexpr int SIZE_PIXELS = 52;
}

// Grid position shouldn't matter and probably should be removed from entity.
// Just calculate from pixel position when needed.
DefaultTower::DefaultTower(float x, float y, bool isKingTower, Player* owner)
  : Tower(x, y, HEALTH, DAMAGE, ATTACK_COOLDOWN, ATTACK_RANGE, SIZE_PIXELS, isKingTower, owner)
{
  auto tex = std::make_shared<sf::Texture>();
  if (!tex->loadFromFile("assets/sprites/tower.png")) {
    throw std::runtime_error("Failed to load tower texture!");
  }

  setTextureShared(tex);

  sf::Vector2u texSize = tex->getSize();

  sprite_.setPosition(static_cast<float>(x), static_cast<float>(y));

  float scaleX = static_cast<float>(SIZE_PIXELS) / static_cast<float>(texSize.x);
  float scaleY = static_cast<float>(SIZE_PIXELS) / static_cast<float>(texSize.y);
  sprite_.setScale(scaleX, scaleY);
}

void DefaultTower::update(float deltaTime) {
  // implement as needed
}