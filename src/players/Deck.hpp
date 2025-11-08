#ifndef DECK_HPP
#define DECK_HPP

#include <vector>

#include "Card.hpp"

class Deck {
 public:
  Deck(const std::vector<Card>& cards);
  void addCard(const Card& card);
  void removeCard(const Card& card);
  const std::vector<Card>& getCards() const;
  std::vector<Card> initializeHand() const;

 private:
  std::vector<Card> cards_;
};

#endif