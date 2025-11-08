#include "Card.hpp"

Card::Card(const std::string& name, int cost, bool isSpell)
    : name_(name), cost_(cost), isSpell_(isSpell) {
  spritePath_ = name + ".png";
}

const std::string& Card::getName() const { return name_; }
int Card::getCost() const { return cost_; }
bool Card::isSpell() const { return isSpell_; }
const std::string& Card::getSpritePath() const { return spritePath_; }
