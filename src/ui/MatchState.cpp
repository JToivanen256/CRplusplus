#include "MatchState.hpp"

#include <iostream>
#include <string>

#include "CardRenderer.hpp"

MatchState::MatchState(Player& p1, Player& p2)
    : player1_(p1), player2_(p2), match_(p1, p2) {
  if (!font_.loadFromFile("assets/fonts/MomoTrustDisplay-Regular.ttf")) {
    std::cerr << "Failed to load font!" << std::endl;
  }
}

void MatchState::update(float deltaTime) { match_.update(deltaTime); }

void MatchState::handleInput(sf::RenderWindow& window, sf::Event event) {
  // Match input
}

void MatchState::render(sf::RenderWindow& window) {
  match_.render(window);
  // Draw Elixir bar and hand here
  sf::Text elixir(std::to_string(player1_.getElixir()), font_, 30);
  elixir.setPosition(187, 735);
  elixir.setFillColor(sf::Color::White);
  window.draw(elixir);

  // Draw player1's hand using CardRenderer
  const auto& cards = player1_.getHand().getCards();
  const float cardW = 40.f;
  const float cardH = 40.f;
  const float gap = 45.f;
  const float startX = 28.f;
  const float y = 695.f - cardH;

  for (size_t i = 0; i < cards.size(); ++i) {
    const auto& card = cards[i];
    float x = startX + i * (cardW + gap);

    CardRenderer::getInstance().renderCard(
        card, window, {x, y}, {cardW / 256.f, cardH / 256.f}
        // need to scale down a lot
    );
  }
}