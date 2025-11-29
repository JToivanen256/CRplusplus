#include "PauseState.hpp"
#include <iostream>

PauseState::PauseState(sf::RenderWindow& window, std::unique_ptr<GameState> previousState)
    : previousState_(std::move(previousState)) {

  // Pause menu setup
  if (!font_.loadFromFile("assets/fonts/MomoTrustDisplay-Regular.ttf")) {
    std::cerr << "Failed to load font!" << std::endl;
  }

  sf::Vector2u size = window.getSize();
  float center = size.x / 2.0f;

  sf::Text resumeOption("Resume", font_, 30);
  resumeOption.setPosition(center - resumeOption.getGlobalBounds().width / 2.0f, 200);
  pauseMenuOptions_.push_back(resumeOption);

  sf::Text menuOption("Menu", font_, 30);
  menuOption.setPosition(center - menuOption.getGlobalBounds().width / 2.0f, 300);
  pauseMenuOptions_.push_back(menuOption);
}

void PauseState::update(float deltaTime) {}

void PauseState::handleInput(sf::RenderWindow& window, sf::Event event) {
  sf::Vector2i mousePos = sf::Mouse::getPosition(window);
  selectedOptionIndex_ = -1;
  for (size_t i = 0; i < pauseMenuOptions_.size(); ++i) {
    if (pauseMenuOptions_[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
      selectedOptionIndex_ = static_cast<int>(i);
      if (selectedOptionIndex_ == 0) {
        pauseMenuOptions_[i].setFillColor(sf::Color::Green);
      } else {
        pauseMenuOptions_[i].setFillColor(sf::Color::Yellow);
      }
    } else {
      pauseMenuOptions_[i].setFillColor(sf::Color::White);
    }
  }

  // Clicking items in the pause menu
  if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && selectedOptionIndex_ != -1) {
    if (selectedOptionIndex_ == 0) {
      resumeGame_ = true;
    } else if (selectedOptionIndex_ == 1) {
      returnToMenu_ = true;
    }
  }
}

void PauseState::render(sf::RenderWindow& window) {
  for (const auto& option : pauseMenuOptions_) {
    window.draw(option);
  }
}

std::unique_ptr<GameState> PauseState::getPreviousState() {
  return std::move(previousState_);
}