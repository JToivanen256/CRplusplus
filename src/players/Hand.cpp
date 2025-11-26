#include "Hand.hpp"

#include <algorithm>

Hand::Hand() {}
Hand::Hand(const std::vector<std::shared_ptr<Card>>& cards) : cards_(cards) {}

void Hand::addCard(const std::shared_ptr<Card>& card) { cards_.push_back(card); }

void Hand::removeCard(const std::shared_ptr<Card>& card) {
  auto it = std::find(cards_.begin(), cards_.end(), card);
  if (it != cards_.end()) cards_.erase(it);
}

const std::vector<std::shared_ptr<Card>>& Hand::getCards() const { return cards_; }