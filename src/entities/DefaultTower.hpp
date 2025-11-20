#ifndef DEFAULTTOWER_HPP
#define DEFAULTTOWER_HPP

#include "Tower.hpp"

class Player;

class DefaultTower : public Tower {
public:
  DefaultTower(int x, int y, bool isKingTower, Player* owner);
  void update(float deltaTime) override;
};

#endif