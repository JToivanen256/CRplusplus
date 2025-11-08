#include "UnitCard.hpp"

UnitCard::UnitCard(const std::string& name, int cost, int health, int damage,
                   int range, bool isBuildingTargeter, float attackCooldown,
                   float movementSpeed)
    : Card(name, cost, false),
      health_(health),
      damage_(damage),
      range_(range),
      isBuildingTargeter_(isBuildingTargeter),
      attackCooldown_(attackCooldown),
      movementSpeed_(movementSpeed) {}

const int UnitCard::getHealth() const { return health_; }
const int UnitCard::getDamage() const { return damage_; }
const int UnitCard::getRange() const { return range_; }
const bool UnitCard::isBuildingTargeter() const { return isBuildingTargeter_; }
const float UnitCard::getAttackCooldown() const { return attackCooldown_; }
const float UnitCard::getMovementSpeed() const { return movementSpeed_; }
