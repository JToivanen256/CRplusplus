#ifndef MATCHSTATE_HPP
#define MATCHSTATE_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "../game/Match.hpp"
#include "../players/Player.hpp"
#include "GameState.hpp"

class MatchState : public GameState {
 private:
  Match match_;
  Player& player1_;
  Player& player2_;
  sf::Font font_;

 public:
  MatchState(Player& p1, Player& p2);
  virtual void update(float deltaTime) override;
  virtual void handleInput(sf::RenderWindow& window, sf::Event event) override;
  virtual void render(sf::RenderWindow& window) override;
};

#endif
