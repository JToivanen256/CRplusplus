#include "MenuState.hpp"
#include <iostream>

MenuState::MenuState(sf::RenderWindow& window) {

  // Main menu setup
  if (!font_.loadFromFile("assets/fonts/MomoTrustDisplay-Regular.ttf")) {
    std::cerr << "Failed to load font!" << std::endl;
  }

  sf::Vector2u size = window.getSize();
  float center = size.x / 2.0f;

  sf::Text playOption("Play", font_, 30);
  playOption.setPosition(center - playOption.getGlobalBounds().width / 2.0f, 200);
  menuOptions_.push_back(playOption);

  sf::Text exitOption("Exit", font_, 30);
  exitOption.setPosition(center - exitOption.getGlobalBounds().width / 2.0f, 300);
  menuOptions_.push_back(exitOption);
}

void MenuState::update(float deltaTime) {}

// Changing menu item color on hover
void MenuState::handleInput(sf::RenderWindow& window, sf::Event event) {
  sf::Vector2i mousePos = sf::Mouse::getPosition(window);
  selectedOptionIndex_ = -1;
  for (size_t i = 0; i < menuOptions_.size(); ++i) {
    if (menuOptions_[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
      selectedOptionIndex_ = static_cast<int>(i);
      if (selectedOptionIndex_ == 0) {
        menuOptions_[i].setFillColor(sf::Color::Green);
      } else {
        menuOptions_[i].setFillColor(sf::Color::Red);
      }
    } else {
      menuOptions_[i].setFillColor(sf::Color::White);
    }
  }

  // Clicking items in the menu
  if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && selectedOptionIndex_ != -1) {
    if (selectedOptionIndex_ == 0) {
      std::cout << "PLAY" << std::endl;
    } else if (selectedOptionIndex_ == 1) {
      window.close();
    }
  }
}

// Rendering menu text
void MenuState::render(sf::RenderWindow& window) {
  for (const auto& option : menuOptions_) {
    window.draw(option);
  }
}
