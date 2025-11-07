#include "MatchState.hpp"

MatchState::MatchState(Player p1, Player p2)
  : match_(p1, p2) {}

void MatchState::update(float deltaTime) {
    match_.update(deltaTime);
}

void MatchState::handleInput(sf::RenderWindow& window, sf::Event event) {
    // Match input
}

void MatchState::render(sf::RenderWindow& window) {
    match_.render(window);
}