#ifndef UNIT_HPP
#define UNIT_HPP

#include "Entity.hpp"


class Unit : public Entity {
protected:
  float movementSpeed_;
  float visionRange_;
  
public:
  Unit(int x, int y, int gridX, int gridY, int health, int damage, float attackCooldown, float attackRange, float movementSpeed, float visionRange);

  virtual void move() = 0;

  //void heal(int amount); ?

};

#endif