#ifndef CARD_HPP
#define CARD_HPP

#include <string>

class Card {
 public:
  Card(const std::string& name, int cost, bool isSpell);
  const std::string& getName() const;
  int getCost() const;
  bool isSpell() const;

 private:
  std::string name_;
  int cost_;
  bool isSpell_;
};

#endif