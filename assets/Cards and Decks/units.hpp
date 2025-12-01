#pragma once

#include "../../src/players/UnitCard.hpp"

// name, cost, health, damage, isBuildingTargeter, attackCooldown,
// movementSpeed, attackRange, visionRange
UnitCard HogRider("Hog Rider", 3, 1500, 300, true, 1.0f, 30.0f, 10.0f, 300.0f);
UnitCard BigRider("Big Rider", 4, 2000, 400, false, 1.5f, 30.0f, 10.0f, 300.0f);
UnitCard MiniRider("Mini Rider", 2, 1000, 200, true, 0.5f, 60.0f, 10.0f,
                   300.0f);
UnitCard FatRider("Fat Rider", 5, 2500, 500, true, 2.0f, 30.0f, 10.0f, 300.0f);
UnitCard DickRider("Dick Rider", 8, 10000, 1000, false, 1.0f, 60.0f, 30.0f,
                   300.0f);
UnitCard RangedRider("Ranged Rider", 4, 1500, 300, false, 3.0f, 30.0f, 40.0f,
                     300.0f);