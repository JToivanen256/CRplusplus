#include "MatchState.hpp"
#include <iostream>
#include <string>

MatchState::MatchState(Player& p1, Player& p2)
  : player1_(p1), player2_(p2), match_(p1, p2) {
    if (!font_.loadFromFile("assets/fonts/MomoTrustDisplay-Regular.ttf")) {
      std::cerr << "Failed to load font!" << std::endl;
    }
  }

void MatchState::update(float deltaTime) {
  match_.update(deltaTime);
}

void MatchState::handleInput(sf::RenderWindow& window, sf::Event event) {
  // Match input
}

void MatchState::render(sf::RenderWindow& window) {
  match_.render(window);
  // Draw Elixir bar and hand here
  sf::Text elixir(std::to_string(player1_.getElixir()), font_, 30);
  elixir.setPosition(10, 700);
  elixir.setFillColor(sf::Color::White);
  window.draw(elixir);
}