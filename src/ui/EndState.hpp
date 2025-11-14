#ifndef ENDSTATE_HPP
#define ENDSTATE_HPP

#include "GameState.hpp"

class EndState : public GameState {
private:
  sf::Font font_;
  std::vector<sf::Text> endMenuOptions_;
  int selectedOptionIndex_ = -1;
  std::string winnerName_;
  sf::Text winnerText_;

public:
  EndState(sf::RenderWindow& window, const std::string& winnerName);
  virtual void update(float deltaTime) override;
  virtual void handleInput(sf::RenderWindow& window, sf::Event event) override;
  virtual void render(sf::RenderWindow& window) override;
  bool returnToMenu_ = false;
};

#endif 