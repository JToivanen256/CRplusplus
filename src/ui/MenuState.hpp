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
  MenuState(sf::RenderWindow& window);
  virtual void update(float deltaTime) override;
  virtual void handleInput(sf::RenderWindow& window, sf::Event event) override;
  virtual void render(sf::RenderWindow& window) override;
  bool ongoingMatch_ = false;
};

#endif
