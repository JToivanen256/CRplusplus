#include "Match.hpp"
#include "../entities/DefaultTower.cpp"

Match::Match(Player& player1, Player& player2)
  : player1_(player1), player2_(player2), map_(30, 50) {
    towers_.emplace_back(std::make_unique<DefaultTower>(169, 39, 13, 3, 1000, 50, 1.5f, 100.0f, 4, true, &player1_));
    towers_.emplace_back(std::make_unique<DefaultTower>(169, 559, 13, 43, 1000, 50, 1.5f, 100.0f, 4, true, &player2_));
  }


void Match::update(float deltaTime) {
    player1_.update(deltaTime);
    player2_.update(deltaTime);
}

void Match::render(sf::RenderWindow& window) {
  map_.getGrid().draw(window);
  for (const auto& tower : towers_) {
    tower->draw(window);
  }
}

void Match::handleInput(sf::Event event) {
  // Handle match input
}