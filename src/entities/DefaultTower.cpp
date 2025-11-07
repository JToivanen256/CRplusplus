#include "Tower.hpp"
#include "../players/Player.hpp"

class DefaultTower : public Tower {
public:
  DefaultTower(int x, int y, int gridX, int gridY, int health, int damage, float attackCooldown, float attackRange, int size, bool isKingTower, Player* owner)
    : Tower(x, y, gridX, gridY, health, damage, attackCooldown, attackRange, size, isKingTower, owner) {}
};