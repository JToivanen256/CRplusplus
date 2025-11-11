#ifndef UNIT_HPP
#define UNIT_HPP

#include "Entity.hpp"
#include "../players/Player.hpp"
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

enum class Direction {None, Up, Down, Left, Right, UpLeft, UpRight, DownLeft, DownRight};


class Unit : public Entity {
protected:
  float movementSpeed_;
  float visionRange_;
  sf::Vector2f posF_{0.f, 0.f};

  using CanMoveFn = std::function<bool(const sf::Vector2f& nextWorldPos)>;
  
  CanMoveFn CanMoveTo_{};
  
  


public:
  Unit(int x, int y, int gridX, int gridY, int health, int damage, float attackCooldown, float attackRange, float movementSpeed, float visionRange, Player* owner)
    : Entity(x, y, gridX, gridY, health, damage, attackCooldown, attackRange, owner), movementSpeed_(movementSpeed), visionRange_(visionRange){}

  void move(Direction dir, float dt);
  void moveToward(const sf::Vector2f& dest, float dt);

  Entity* scanNearestEnemy(const std::vector<Entity*>& all)const;

  void drawVision(sf::RenderWindow& window, bool visible = true)const;

  void syncVisual();

  //void heal(int amount); ?

};

#endif