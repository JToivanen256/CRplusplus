#ifndef MATCH_HPP
#define MATCH_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>

#include "../entities/Building.hpp"
#include "../entities/Projectile.hpp"
#include "../entities/Spell.hpp"
#include "../entities/Tower.hpp"
#include "../entities/Unit.hpp"
#include "../players/Player.hpp"
#include "../players/UnitCard.hpp"
#include "Map.hpp"

class Match {
 private:
  Player& player1_;
  Player& player2_;
  Map map_;
  Player* winner_ = nullptr;
  std::vector<std::unique_ptr<Unit>> units_;
  std::vector<std::unique_ptr<Building>> buildings_;
  std::vector<std::unique_ptr<Tower>> towers_;
  std::vector<std::unique_ptr<Projectile>> projectiles_;
  std::vector<std::unique_ptr<Spell>> spells_;
  float matchTime_ = 0.0f;
  const float maxMatchTime_ = 180.0f;

  void checkForWinner();

  sf::Texture basicTestUnitTexture_;

 public:
  Match(Player& player1, Player& player2);

  void update(float deltaTime);
  void render(sf::RenderWindow& window);
  void handleInput(sf::Event event);

  bool isOver() const;
  Player* winner() const;

  float getRemainingTime() const;
  std::vector<std::unique_ptr<Unit>>& getUnits();

  Map& getMap();
  const Map& getMap() const;

  // Add a unit to the match (takes ownership)
  void addUnit(std::unique_ptr<Unit> unit);

  // Debug
  void printUnitPositions() const {
    for (const auto& unit : units_) {
      GridPos gridPos = unit->getGridPosition();
      std::cout << "Unit at grid (" << gridPos.x << ", " << gridPos.y << ")\n";
    }
  }
  void createUnitFromCard(const UnitCard& card, int gridX, int girdY,
                          Player& owner);
};

#endif