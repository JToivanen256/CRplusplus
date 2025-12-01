#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include "GameState.hpp"
#include <memory>

class PauseState : public GameState {
private:
  sf::Font font_;
  std::vector<sf::Text> pauseMenuOptions_;
  int selectedOptionIndex_ = -1;
  std::unique_ptr<GameState> previousState_; // Store the previous state to resume later

public:
  PauseState(sf::RenderWindow& window, std::unique_ptr<GameState> previousState);
  virtual void update(float deltaTime) override;
  virtual void handleInput(sf::RenderWindow& window, sf::Event event) override;
  virtual void render(sf::RenderWindow& window) override;
  bool resumeGame_ = false;
  bool returnToMenu_ = false;
  std::unique_ptr<GameState> getPreviousState();
};



#endif