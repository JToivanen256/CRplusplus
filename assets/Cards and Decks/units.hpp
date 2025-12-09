#pragma once

#include "../../src/players/UnitCard.hpp"

// name, cost, health, damage, isBuildingTargeter, attackCooldown,
// movementSpeed, attackRange, visionRange
UnitCard HogRider("Hog Rider", 3, 1500, 300, true, 1.0f, 30.0f, 10.0f,
                  150.0f);  // As in clash royale itself
UnitCard BigRider("Big Rider", 4, 2000, 400, false, 1.5f, 30.0f, 10.0f,
                  150.0f);  // Non-building targeter
UnitCard MiniRider("Mini Rider", 2, 1000, 200, true, 0.5f, 60.0f, 10.0f,
                   150.0f);  // Fast small unit
UnitCard FatRider("Fat Rider", 5, 2500, 500, true, 2.0f, 30.0f, 70.0f,
                  150.0f);  // Tanky unit
UnitCard DickRider("Dick Rider", 8, 3000, 1000, false, 1.0f, 60.0f, 30.0f,
                   150.0f);  // Completely overpowered meme unit
UnitCard RangedRider("Ranged Rider", 4, 1500, 300, false, 3.0f, 30.0f, 70.0f,
                     150.0f);  // Ranged unit