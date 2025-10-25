#ifndef TOWER_HPP
#define TOWER_HPP

#include "Building.hpp"

class Tower : public Building {
protected:
  bool isKingTower_;

public:
  Tower(int x, int y, bool isKingTower);

};

#endif