#ifndef TOWER_HPP
#define TOWER_HPP

#include "Building.hpp"
#include "../players/Player.hpp"

class Tower : public Building {
protected:
  bool isKingTower_;

public:
  Tower(int x, int y, int health, int damage, float attackCooldown, float attackRange, int size, bool isKingTower, Player* owner)
    : Building(x, y, health, damage, attackCooldown, attackRange, size, owner), isKingTower_(isKingTower) {}

  bool isKingTower() const {
    return isKingTower_;
  }
};

#endif