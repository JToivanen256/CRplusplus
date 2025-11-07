#include "Match.hpp"

Match::Match(Player player1, Player player2)
  : player1_(player1), player2_(player2), map_(10, 10) {
}

void Match::update(float deltaTime) {
    // Update match logic
}

void Match::render(sf::RenderWindow& window) {
    // Render match elements
}

void Match::handleInput(sf::Event event) {
    // Handle match input
}