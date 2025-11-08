#pragma once

#include "Card.hpp"

class UnitCard : public Card {
 public:
  UnitCard(const std::string& name, int cost, int health, int damage, int range,
           bool isBuildingTargeter, float attackCooldown, float movementSpeed);
  const int getHealth() const;
  const int getDamage() const;
  const int getRange() const;
  const bool isBuildingTargeter() const;
  const float getAttackCooldown() const;
  const float getMovementSpeed() const;

 private:
  int health_;
  int damage_;
  int range_;
  bool isBuildingTargeter_;
  float attackCooldown_;
  float movementSpeed_;
};