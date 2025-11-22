#ifndef TESTUNIT_HPP
#define TESTUNIT_HPP
#include "Unit.hpp"

class TestUnit : public Unit {
 public:
  TestUnit(int worldX, int worldY, int gridX, int gridY, Player* owner)
      : Unit(worldX, worldY, gridX, gridY,
             /*health*/ 100,
             /*damage*/ 10,
             /*attackCooldown*/ 0.6f,
             /*attackRange*/ 30.f,
             /*movementSpeed*/ 80.f,
             /*visionRange*/ 160.f, owner) {
    sf::Image img;
    img.create(20, 20, sf::Color::Black);

    sf::Texture tex;
    tex.loadFromImage(img);
    setTexture(tex);
    syncVisual();
  }

  void update(float deltaTime) override {
    // For now, no AI movement — just keep visual in sync
    syncVisual();
  }
};

#endif
