#ifndef UNIT_HPP
#define UNIT_HPP

#include "Entity.hpp"


class Unit : public Entity {
protected:
  int health_;
  int damage_;
  float attackCooldown_;
  float attackRange_;
  float movementSpeed_;
  float visionRange_;
  
public:
  Unit(int x, int y) : Entity(x, y) {}

  virtual void move() = 0;
  virtual void attack() = 0;

  void takeDamage(int amount);

  //void heal(int amount); ?

  void die();

};

#endif