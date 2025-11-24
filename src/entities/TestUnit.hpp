#ifndef TESTUNIT_HPP
#define TESTUNIT_HPP
#include "Unit.hpp"

class TestUnit : public Unit {
 public:
  TestUnit(int worldX, int worldY, Player* owner)
      : Unit(worldX, worldY,
             /*health*/ 100,
             /*damage*/ 10,
             /*attackCooldown*/ 0.6f,
             /*attackRange*/ 30.f,
             /*movementSpeed*/ 20.f,
             /*visionRange*/ 160.f, owner, "TESTUNIT") {
    sf::Image img;
    img.create(20, 20, sf::Color::Black);

    sf::Texture tex;
    tex.loadFromImage(img);
    setTexture(tex);
    syncVisual();
  }

  void update(float deltaTime) override {
    moveToward(targetPosition_, deltaTime);
    syncVisual();
  }
};

#endif
