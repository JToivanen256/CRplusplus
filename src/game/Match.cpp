#include "Match.hpp"

Match::Match(Player& player1, Player& player2)
  : player1_(player1), player2_(player2), map_(30, 50) {
}

void Match::update(float deltaTime) {
    player1_.update(deltaTime);
    player2_.update(deltaTime);
}

void Match::render(sf::RenderWindow& window) {
  map_.getGrid().draw(window);
}

void Match::handleInput(sf::Event event) {
  // Handle match input
}