#pragma once

#include "../../src/players/UnitCard.hpp"

// name, cost, health, damage, range, isBuildingTargeter, attackCooldown,
// movementSpeed
UnitCard HogRider("Hog Rider", 4, 1500, 300, 1, true, 1.0f, 2.0f);
UnitCard BigRider("Big Rider", 5, 2000, 400, 1, false, 1.5f, 1.5f);
UnitCard MiniRider("Mini Rider", 3, 1000, 200, 1, true, 0.5f, 3.0f);
UnitCard FatRider("Fat Rider", 6, 2500, 500, 1, true, 2.0f, 1.0f);
UnitCard DickRider("Dick Rider", 10, 10000, 1000, 1, false, 1.0f, 2.0f);
UnitCard RangedRider("Ranged Rider", 5, 1500, 300, 5, false, 1.0f, 1.5f);