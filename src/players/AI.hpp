#ifndef AI_HPP
#define AI_HPP

#include "Player.hpp"

class AI {
public:
  AI(Player& p) : player(p) {}

  void play() const; // AI Strategy

private:
  Player& player;
};

#endif