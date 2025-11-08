#pragma once

#include "Card.hpp"

class SpellCard : public Card {
 public:
  SpellCard(const std::string& name, int cost, int damage, int radius);
  const int getDamage() const;
  const int getRadius() const;

 private:
  int damage_;
  int radius_;
};