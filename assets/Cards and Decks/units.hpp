#pragma once

#include "../../src/players/UnitCard.hpp"

// name, cost, health, damage, range, isBuildingTargeter, attackCooldown,
// movementSpeed, attackRange, visionRange
UnitCard HogRider("Hog Rider", 4, 1500, 300, true, 1.0f, 30.0f, 10.0f, 250.0f);
UnitCard BigRider("Big Rider", 5, 2000, 400, false, 1.5f, 30.0f, 10.0f, 250.0f);
UnitCard MiniRider("Mini Rider", 3, 1000, 200, true, 0.5f, 30.0f, 10.0f, 250.0f);
UnitCard FatRider("Fat Rider", 6, 2500, 500, true, 2.0f, 30.0f, 10.0f, 250.0f);
UnitCard DickRider("Dick Rider", 10, 10000, 1000, false, 1.0f, 30.0f, 10.0f, 250.0f);
UnitCard RangedRider("Ranged Rider", 5, 1500, 300, false, 1.0f, 30.0f, 10.0f, 250.0f);