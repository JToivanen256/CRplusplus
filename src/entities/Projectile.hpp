#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include "../players/Player.hpp"

class Projectile {
protected:
  float speed_;
  int damage_;
  Pos position_;
  Pos targetPosition_;
  sf::Sprite sprite_;
  sf::Texture texture_;
  Player* owner_;


public:
  Projectile(int x, int y, float speed, int damage, Pos targetPosition, Player* owner);

  void move();

};

#endif