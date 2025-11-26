#ifndef HAND_HPP
#define HAND_HPP

#include <vector>
#include <memory>

#include "Card.hpp"


class Hand {
public:
  Hand();
  Hand(const std::vector<std::shared_ptr<Card>>& cards);
  void addCard(const std::shared_ptr<Card>& card);
  void removeCard(const std::shared_ptr<Card>& card);
  const std::vector<std::shared_ptr<Card>>& getCards() const;

private:
  std::vector<std::shared_ptr<Card>> cards_;
};

#endif