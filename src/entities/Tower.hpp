#ifndef TOWER_HPP
#define TOWER_HPP

#include "Building.hpp"

class Tower : public Building {
protected:
  bool isKingTower_;

public:
  Tower(int x, int y, int gridX, int gridY, int health, int damage, float attackCooldown, float attackRange, int size, bool isKingTower, Player* owner)
    : Building(x, y, gridX, gridY, health, damage, attackCooldown, attackRange, size, owner), isKingTower_(isKingTower) {}

};

#endif