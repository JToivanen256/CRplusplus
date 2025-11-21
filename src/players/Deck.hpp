#ifndef DECK_HPP
#define DECK_HPP

#include <vector>

#include "Card.hpp"

class Deck {
 public:
  Deck(const std::vector<Card>& cards);
  void addCard(const Card& card);
  void removeCard(const Card& card);
  void playCard(const Card& card);
  void shuffle();
  std::vector<Card> getHand() const;
  std::vector<Card> initializedHand();
  const std::vector<Card>& getCards() const;

 private:
  std::vector<Card> cards_;
};

#endif