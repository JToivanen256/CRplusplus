#include "SpellCard.hpp"

SpellCard::SpellCard(const std::string& name, int cost, int damage, int radius)
    : Card(name, cost, true), damage_(damage), radius_(radius) {}

const int SpellCard::getDamage() const { return damage_; }
const int SpellCard::getRadius() const { return radius_; }
