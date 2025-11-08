#include "spell.hpp"

spell::spell(const std::string& name, int cost, int damage, int radius)
    : Card(name, cost, true), damage_(damage), radius_(radius) {}

const int spell::getDamage() const { return damage_; }
const int spell::getRadius() const { return radius_; }
