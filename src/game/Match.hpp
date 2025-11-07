#ifndef MATCH_HPP
#define MATCH_HPP

#include "../players/Player.hpp"
#include "Map.hpp"


class Match {
private:
  Player player1_;
  Player player2_;
  Map map_;

public:
  Match(Player player1, Player player2);

  void update(float deltaTime);
  void render(sf::RenderWindow& window);
  void handleInput(sf::Event event);
};

#endif