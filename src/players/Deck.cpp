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

void Deck::playCard(const Card& card) {
  auto it = std::find_if(cards_.begin(), cards_.end(), [&card](const Card& c) {
    return c.getName() == card.getName();
  });
  if (it != cards_.end()) {
    Card played = *it;
    cards_.erase(it);          // remove from current position
    cards_.push_back(played);  // move to back
  } else {
    throw std::invalid_argument("Card not found in deck.");
  }
}

const std::vector<Card>& Deck::getCards() const { return cards_; }

void Deck::shuffle() {  // Used when initializing hand
  std::mt19937 rng{std::random_device{}()};
  std::shuffle(cards_.begin(), cards_.end(), rng);
}

std::vector<Card> Deck::getHand() const {  // First 4 cards
  return std::vector<Card>(cards_.begin(), cards_.begin() + 4);
}

std::vector<Card> Deck::initializedHand() {
  this->shuffle();
  return this->getHand();
}