#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>

#include "../players/AI.hpp"  //To not have the AIDifficulty enum everywhere

class GameState {
 public:
  virtual ~GameState() = default;
  virtual void update(float deltaTime) = 0;
  virtual void handleInput(sf::RenderWindow& window, sf::Event event) = 0;
  virtual void render(sf::RenderWindow& window) = 0;
};

#endif