#include "Tower.hpp"
#include "../players/Player.hpp"

class DefaultTower : public Tower {
public:
  DefaultTower(int x, int y, int gridX, int gridY, int health, int damage, float attackCooldown, float attackRange, int size, bool isKingTower, Player* owner)
    : Tower(x, y, gridX, gridY, health, damage, attackCooldown, attackRange, size, isKingTower, owner) {
      if (!texture_.loadFromFile("assets/sprites/tower.png")) {
        throw std::runtime_error("Failed to load tower texture!");
      }

      sprite_.setTexture(texture_);

      sprite_.setPosition(static_cast<float>(x), static_cast<float>(y));

      sf::Vector2u texSize = texture_.getSize(); 

      float scaleX = 52.f / texSize.x;
      float scaleY = 52.f / texSize.y;

      sprite_.setScale(scaleX, scaleY);
    }

  void update(float deltaTime) override {};
};