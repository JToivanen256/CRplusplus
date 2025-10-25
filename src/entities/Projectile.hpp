#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Entity.hpp"

class Projectile : public Entity {
protected:
  float speed_;
  int damage_;

public:
  Projectile(int x, int y, float speed, int damage);

  void move();

};

#endif