#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Entity.hpp"
#include <SFML/Graphics.hpp>

struct Pos {
  int x;
  int y;
};

class Projectile {
protected:
  float speed_;
  int damage_;
  Pos position_;
  Pos targetPosition_;
  sf::Sprite sprite_;
  sf::Texture texture_;


public:
  Projectile(int x, int y, float speed, int damage, Pos targetPosition);

  void move();

};

#endif