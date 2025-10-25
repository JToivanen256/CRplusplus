#ifndef HAND_HPP
#define HAND_HPP

#include <vector>
#include "Card.hpp"

class Hand {
public:
  Hand();
  void addCard(const Card& card);
  void removeCard(const Card& card);
  const std::vector<Card>& getCards() const;

private:
  std::vector<Card> cards_;
};

#endif