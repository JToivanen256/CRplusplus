#include "MenuState.hpp"
#include <iostream>

MenuState::MenuState() {
  if (!font_.loadFromFile("../assets/fonts/MomoTrustDisplay-Regular.ttf")) {
    std::cerr << "Failed to load font!" << std::endl;
  }


  sf::Text playOption("Play", font_, 30);
  playOption.setPosition(100, 100);
  playOption.setFillColor(sf::Color::White);
  menuOptions_.push_back(playOption);

  sf::Text exitOption("Exit", font_, 30);
  exitOption.setPosition(100, 200);
  exitOption.setFillColor(sf::Color::White);
  menuOptions_.push_back(exitOption);
}

void MenuState::update(float deltaTime) {}

void MenuState::handleInput(sf::RenderWindow& window) {
  sf::Vector2i mousePos = sf::Mouse::getPosition(window);
  selectedOptionIndex_ = -1;
  for (size_t i = 0; i < menuOptions_.size(); ++i) {
    if (menuOptions_[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
      selectedOptionIndex_ = static_cast<int>(i);
      menuOptions_[i].setFillColor(sf::Color::Red);
    } else {
      menuOptions_[i].setFillColor(sf::Color::White);
    }
  }
}

void MenuState::render(sf::RenderWindow& window) {
  for (const auto& option : menuOptions_) {
    window.draw(option);
  }
}
