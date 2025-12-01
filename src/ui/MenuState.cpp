#include "MenuState.hpp"

#include <iostream>

MenuState::MenuState(sf::RenderWindow& window) {
  // Main menu setup
  if (!font_.loadFromFile("assets/fonts/MomoTrustDisplay-Regular.ttf")) {
    std::cerr << "Failed to load font!" << std::endl;
  }

  sf::Vector2u size = window.getSize();
  float center = size.x / 2.0f;

  sf::Text difficultySelectionTitle("Select difficulty:", font_, 30);
  difficultySelectionTitle.setPosition(
      center - difficultySelectionTitle.getGlobalBounds().width / 2.0f, 50);
  menuOptions_.push_back(difficultySelectionTitle);

  sf::Text vihannesOption("Vihannes", font_, 30);
  vihannesOption.setPosition(
      center - vihannesOption.getGlobalBounds().width / 2.0f, 150);
  menuOptions_.push_back(vihannesOption);

  sf::Text retardiOption("Retardi", font_, 30);
  retardiOption.setPosition(
      center - retardiOption.getGlobalBounds().width / 2.0f, 200);
  menuOptions_.push_back(retardiOption);

  sf::Text cheaterOption("Cheater", font_, 30);
  cheaterOption.setPosition(
      center - cheaterOption.getGlobalBounds().width / 2.0f, 250);
  menuOptions_.push_back(cheaterOption);

  sf::Text playOption("Play", font_, 30);
  playOption.setPosition(center - playOption.getGlobalBounds().width / 2.0f,
                         350);
  menuOptions_.push_back(playOption);

  sf::Text exitOption("Exit", font_, 30);
  exitOption.setPosition(center - exitOption.getGlobalBounds().width / 2.0f,
                         450);
  menuOptions_.push_back(exitOption);
}

void MenuState::update(float deltaTime) {}

// Changing menu item color on hover and size on click
void MenuState::handleInput(sf::RenderWindow& window, sf::Event event) {
  sf::Vector2i mousePos = sf::Mouse::getPosition(window);
  selectedOptionIndex_ = -1;

  for (size_t i = 0; i < menuOptions_.size(); ++i) {
    if (menuOptions_[i].getGlobalBounds().contains(
            static_cast<sf::Vector2f>(mousePos))) {
      selectedOptionIndex_ = static_cast<int>(i);

      // Hover colors
      if (selectedOptionIndex_ == 4) {
        menuOptions_[i].setFillColor(sf::Color::Green);
      } else if (selectedOptionIndex_ == 5) {
        menuOptions_[i].setFillColor(sf::Color::Red);
      } else if (selectedOptionIndex_ != 0) {
        menuOptions_[i].setFillColor(sf::Color::Yellow);
      }

      // If mouse is pressed down, shrink button text slightly
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
          selectedOptionIndex_ != 0) {
        menuOptions_[i].setScale(0.9f, 0.9f);  // shrink
      } else {
        menuOptions_[i].setScale(1.f, 1.f);  // reset size
      }
    } else {
      menuOptions_[i].setFillColor(sf::Color::White);
      menuOptions_[i].setScale(1.f, 1.f);  // reset size if not hovered anymore
    }
  }

  // Clicking items in the menu
  if (event.type == sf::Event::MouseButtonReleased &&
      event.mouseButton.button == sf::Mouse::Left &&
      selectedOptionIndex_ != -1) {
    if (selectedOptionIndex_ == 1) {
      selectedAIDifficulty_ = Vihannes;
    } else if (selectedOptionIndex_ == 2) {
      selectedAIDifficulty_ = Retardi;
    } else if (selectedOptionIndex_ == 3) {
      selectedAIDifficulty_ = Cheater;
    } else if (selectedOptionIndex_ == 4) {
      ongoingMatch_ = true;
    } else if (selectedOptionIndex_ == 5) {
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
