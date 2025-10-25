#ifndef CARD_HPP
#define CARD_HPP

#include <string>

class Card {
public:
  Card(const std::string& name, int cost);
  const std::string& getName() const;
  int getCost() const;

private:
  std::string name_;
  int cost_;
};

#endif