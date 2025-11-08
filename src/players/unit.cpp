#include "unit.hpp"

unit::unit(const std::string& name, int cost, int health, int damage, int range,
           bool isBuildingTargeter, float attackCooldown, float movementSpeed)
    : Card(name, cost, false),
      health_(health),
      damage_(damage),
      range_(range),
      isBuildingTargeter_(isBuildingTargeter),
      attackCooldown_(attackCooldown),
      movementSpeed_(movementSpeed) {}

const int unit::getHealth() const { return health_; }
const int unit::getDamage() const { return damage_; }
const int unit::getRange() const { return range_; }
const bool unit::isBuildingTargeter() const { return isBuildingTargeter_; }
const float unit::getAttackCooldown() const { return attackCooldown_; }
const float unit::getMovementSpeed() const { return movementSpeed_; }
