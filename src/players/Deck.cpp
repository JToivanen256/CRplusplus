#include "Deck.hpp"

#include <algorithm>
#include <random>
#include <stdexcept>

Deck::Deck(const std::vector<Card>& cards) : cards_(cards) {
  if (cards.size() != 8) {
    throw std::invalid_argument("Deck must contain exactly 8 cards.");
  }
}

void Deck::addCard(const Card& card) {
  if (cards_.size() < 8) {
    cards_.push_back(card);
  } else {
    throw std::invalid_argument("Deck cannot contain more than 8 cards.");
  }
}

void Deck::removeCard(const Card& card) {
  auto it = std::find_if(cards_.begin(), cards_.end(), [&card](const Card& c) {
    return c.getName() == card.getName();
  });
  if (it != cards_.end()) {
    cards_.erase(it);
  }
}

const std::vector<Card>& Deck::getCards() const { return cards_; }

std::vector<Card> Deck::initializeHand() const {
  std::vector<Card> hand;
  std::sample(cards_.begin(), cards_.end(), std::back_inserter(hand), 4,
              std::mt19937{std::random_device{}()});
  return hand;
}
