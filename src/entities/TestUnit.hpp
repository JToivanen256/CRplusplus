#ifndef TESTUNIT_HPP
#define TESTUNIT_HPP
#include "Unit.hpp"
#include <iostream>

class TestUnit : public Unit {
 public:
  TestUnit(float x, float y, int health, int damage,
           float attackCooldown, float attackRange, float movementSpeed,
           float visionRange, Player* owner, const std::string& name)
      : Unit(x, y, health, damage, attackCooldown, attackRange, movementSpeed,
             visionRange, owner, name) {
    sf::Image img;
    img.create(20, 20, sf::Color::Black);

    sf::Texture tex;
    tex.loadFromImage(img);
    setTexture(tex);
    syncVisual();
  }
};

#endif
