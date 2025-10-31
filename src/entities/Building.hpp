#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "Entity.hpp"

class Building : public Entity {
protected:
  int health_;
  int damage_;
  float attackCooldown_;
  float attackRange_;
  int size_;

public:
  Building(int x, int y, int gridX, int gridY, int health, int damage, float attackCooldown, float attackRange, int size);

  virtual void attack() = 0;

  void takeDamage(int amount);

  void die();
};
#endif