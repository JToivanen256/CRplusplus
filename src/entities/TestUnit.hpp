#ifndef TESTUNIT_HPP
#define TESTUNIT_HPP
#include "Unit.hpp"
#include <iostream>

class TestUnit : public Unit {
 public:
  TestUnit(int worldX, int worldY, Player* owner)
      : Unit(worldX, worldY,
             /*health*/ 100,
             /*damage*/ 10,
             /*attackCooldown*/ 0.6f,
             /*attackRange*/ 10.f,
             /*movementSpeed*/ 20.f,
             /*visionRange*/ 500.f, owner, "TESTUNIT") {
    sf::Image img;
    img.create(20, 20, sf::Color::Black);

    sf::Texture tex;
    tex.loadFromImage(img);
    setTexture(tex);
    syncVisual();
  }
};

#endif
