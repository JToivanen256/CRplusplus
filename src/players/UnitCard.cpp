#include "UnitCard.hpp"

UnitCard::UnitCard(const std::string& name, int cost, int health, int damage,
                   bool isBuildingTargeter, float attackCooldown,
                   float movementSpeed, float attackRange, float visionRange)
    : Card(name, cost, false),
      health_(health),
      damage_(damage),
      attackRange_(attackRange),
      visionRange_(visionRange),
      isBuildingTargeter_(isBuildingTargeter),
      attackCooldown_(attackCooldown),
      movementSpeed_(movementSpeed) {}

const int UnitCard::getHealth() const { return health_; }
const int UnitCard::getDamage() const { return damage_; }
const float UnitCard::getVisionRange() const { return visionRange_; }
const float UnitCard::getAttackRange() const { return attackRange_; }
const bool UnitCard::isBuildingTargeter() const { return isBuildingTargeter_; }
const float UnitCard::getAttackCooldown() const { return attackCooldown_; }
const float UnitCard::getMovementSpeed() const { return movementSpeed_; }
