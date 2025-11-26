#ifndef DECK_HPP
#define DECK_HPP

#include <vector>
#include <memory>

#include "Card.hpp"

class Deck {
public:
  Deck(const std::vector<std::shared_ptr<Card>>& cards);
  void addCard(const std::shared_ptr<Card>& card);
  void removeCard(const std::shared_ptr<Card>& card);
  void playCard(const std::shared_ptr<Card>& card);
  const std::vector<std::shared_ptr<Card>>& getCards() const;
  std::vector<std::shared_ptr<Card>> getHand() const;
  void shuffle();
  std::vector<std::shared_ptr<Card>> initializedHand();
private:
  std::vector<std::shared_ptr<Card>> cards_;
};

#endif