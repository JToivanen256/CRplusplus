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

};


#endif MATCH_HPP