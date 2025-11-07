#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "Entity.hpp"

class Building : public Entity {
protected:
  int size_;

public:
  Building(int x, int y, int gridX, int gridY, int health, int damage, float attackCooldown, float attackRange, int size, Player* owner)
    : Entity(x, y, gridX, gridY, health, damage, attackCooldown, attackRange, owner), size_(size) {}

};
#endif