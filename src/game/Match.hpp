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

  template <typename T, typename... Args>
  T& Match::spawnUnit(Args&&... args){
    static_assert(std::is_base_of_v<Unit, T>, "Must be a type of Unit");

    auto uptr = std::make_unique<T>(std::forward<Args>(args)...);
    T& ref = *uptr;
    units.push_back(std::move(uptr));
    return ref;
  }


  /**
   * Use this method for spawning units on the grid.
   * Usageway: match.spawnUnitOnGrid<Unittype>(gridX, gridY, owner) with
   * Unittype replaced with the class of unit you want to spawn on the grid
   */
  template <typename T, typename... Args>
  T& spawnUnitOnGrid(int gridX, int gridY, Player& owner, Args&&... extra){

    Grid& grid = map_.getGrid();
    int tileSize = getTileSizeFromGrid(grid);

    int worldX = gridX * tileSize + tileSize / 2;
    int worldY = gridY * tileSize + tileSize / 2;

    return spawnUnit<T>(worldX, worldY, gridX, gridY, &owner, std::forward<Args>(extra)...);
  }  


};

static inline int getTileSizeFromGrid(Grid& g) {
    return static_cast<int>(g.at(0, 0).getSize().x);
}


#endif