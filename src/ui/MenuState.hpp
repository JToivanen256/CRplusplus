#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include <vector>


class MenuState : public GameState {
private:
  sf::Font font_;
  std::vector<sf::Text> menuOptions_;
  int selectedOptionIndex_ = -1;

public:
  MenuState();
  virtual void update(float deltaTime) override;
  virtual void handleInput(sf::RenderWindow& window) override;
  virtual void render(sf::RenderWindow& window) override;
};

#endif
