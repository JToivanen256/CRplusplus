#ifndef DECK_HPP
#define DECK_HPP

#include <vector>
#include "Card.hpp"

class Deck {
public:
  Deck();
  void addCard(const Card& card);
  void removeCard(const Card& card);
  const std::vector<Card>& getCards() const;

private:
  std::vector<Card> cards_;
};

#endif