#ifndef MATCH_HPP
#define MATCH_HPP

#include "../players/Player.hpp"
#include "Map.hpp"
#include <vector>
#include "../entities/Unit.hpp"
#include "../entities/Building.hpp"
#include "../entities/Tower.hpp"
#include "../entities/Projectile.hpp"
#include "../entities/Spell.hpp"
#include <memory>

class Match {
private:
  Player& player1_;
  Player& player2_;
  Map map_;
  std::vector<std::unique_ptr<Unit>> units;
  std::vector<std::unique_ptr<Building>> buildings;
  std::vector<std::unique_ptr<Tower>> towers;
  std::vector<std::unique_ptr<Projectile>> projectiles;
  std::vector<std::unique_ptr<Spell>> spells;

public:
  Match(Player& player1, Player& player2);

  void update(float deltaTime);
  void render(sf::RenderWindow& window);
  void handleInput(sf::Event event);
};

#endif