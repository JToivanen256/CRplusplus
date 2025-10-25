#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "Entity.hpp"

class Building : public Entity {
protected:
  int health_;
  int damage_;
  float attackCooldown_;
  float attackRange_;
  int width_;
  int height_;

public:
  Building(int x, int y) : Entity(x, y) {}

  virtual void attack() = 0;

  void takeDamage(int amount);

  void die();
};
#endif