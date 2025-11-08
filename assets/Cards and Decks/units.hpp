#pragma once

#include "../../src/players/unit.hpp"

// name, cost, health, damage, range, isBuildingTargeter, attackCooldown,
// movementSpeed
unit HogRider("Hog Rider", 4, 1500, 300, 1, true, 1.0f, 2.0f);
unit BigRider("Big Rider", 5, 2000, 400, 1, false, 1.5f, 1.5f);
unit MiniRider("Mini Rider", 3, 1000, 200, 1, true, 0.5f, 3.0f);
unit FatRider("Fat Rider", 6, 2500, 500, 1, true, 2.0f, 1.0f);
unit DickRider("Dick Rider", 10, 10000, 1000, 1, false, 1.0f, 2.0f);
unit RangedRider("Ranged Rider", 5, 1500, 300, 5, false, 1.0f, 1.5f);