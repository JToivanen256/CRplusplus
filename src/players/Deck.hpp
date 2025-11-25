#ifndef DECK_HPP
#define DECK_HPP

#include <vector>
#include <memory>

#include "Card.hpp"

/*
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
*/

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