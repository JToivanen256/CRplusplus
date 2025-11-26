#pragma once

#include "../../src/players/UnitCard.hpp"

// name, cost, health, damage, range, isBuildingTargeter, attackCooldown,
// movementSpeed, attackRange, visionRange
UnitCard HogRider("Hog Rider", 1, 1500, 300, true, 1.0f, 30.0f, 10.0f, 300.0f);
UnitCard BigRider("Big Rider", 1, 2000, 400, false, 1.5f, 30.0f, 10.0f, 300.0f);
UnitCard MiniRider("Mini Rider", 1, 1000, 200, true, 0.5f, 30.0f, 10.0f, 300.0f);
UnitCard FatRider("Fat Rider", 1, 2500, 500, true, 2.0f, 30.0f, 10.0f, 300.0f);
UnitCard DickRider("Dick Rider", 1, 10000, 1000, false, 1.0f, 30.0f, 10.0f, 300.0f);
UnitCard RangedRider("Ranged Rider", 1, 1500, 300, false, 1.0f, 30.0f, 10.0f, 300.0f);