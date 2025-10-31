#include "Tower.hpp"

class DefaultTower : public Tower {
public:
  DefaultTower(int x, int y, int gridX, int gridY, int health, int damage, float attackCooldown, float attackRange, int size, bool isKingTower)
    : Tower(x, y, gridX, gridY, health, damage, attackCooldown, attackRange, size, isKingTower) {}
};