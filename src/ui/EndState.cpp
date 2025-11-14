#include "EndState.hpp"
#include <iostream>

EndState::EndState(sf::RenderWindow& window, const std::string& winnerName) : winnerName_(winnerName) {
  // Setup end of game state
  if (!font_.loadFromFile("assets/fonts/MomoTrustDisplay-Regular.ttf")) {
    std::cerr << "Failed to load font!" << std::endl;
  }
  sf::Vector2u size = window.getSize();
  float center = size.x / 2.0f;

  winnerText_.setFont(font_);
  winnerText_.setCharacterSize(40);
  winnerText_.setFillColor(sf::Color::Yellow);
  winnerText_.setString(winnerName_ + " Wins!");
  winnerText_.setPosition(center - winnerText_.getGlobalBounds().width / 2.0f, 150);

  sf::Text menuOption("Return to Menu", font_, 30);
  menuOption.setPosition(center - menuOption.getGlobalBounds().width / 2.0f, 300);
  endMenuOptions_.push_back(menuOption);

  sf::Text exitOption("Exit", font_, 30);
  exitOption.setPosition(center - exitOption.getGlobalBounds().width / 2.0f, 400);
  endMenuOptions_.push_back(exitOption);
}

void EndState::update(float deltaTime) {}

void EndState::handleInput(sf::RenderWindow& window, sf::Event event) {
  sf::Vector2i mousePos = sf::Mouse::getPosition(window);
  selectedOptionIndex_ = -1;
  for (size_t i = 0; i < endMenuOptions_.size(); ++i) {
    if (endMenuOptions_[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
      selectedOptionIndex_ = static_cast<int>(i);
      endMenuOptions_[i].setFillColor(sf::Color::Green);
    } else {
      endMenuOptions_[i].setFillColor(sf::Color::White);
    }
  }

  // Clicking items in the end menu
  if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && selectedOptionIndex_ != -1) {
    if (selectedOptionIndex_ == 0) {
      returnToMenu_ = true;
    } else if (selectedOptionIndex_ == 1) {
      window.close();
    }
  }
}

void EndState::render(sf::RenderWindow& window) {
  window.draw(winnerText_);
  for (const auto& option : endMenuOptions_) {
    window.draw(option);
  }
}