#ifndef UNIT_HPP
#define UNIT_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <vector>

#include "../players/Player.hpp"
#include "Entity.hpp"

enum class Direction {
  None,
  Up,
  Down,
  Left,
  Right,
  UpLeft,
  UpRight,
  DownLeft,
  DownRight
};
enum class State { Moving, Attacking };
class Unit : public Entity {
 protected:
  sf::Vector2f targetPosition_;
  float movementSpeed_;
  float visionRange_;
  std::string name_;  // Debug
  std::vector<sf::Vector2f> path_;
  size_t currentPathIndex_ = 0;
  sf::Vector2f lastTargetPoint_{0.f,0.f};

  using CanMoveFn = std::function<bool(const sf::Vector2f& nextWorldPos)>;

  CanMoveFn CanMoveTo_{};

  State currentState_ = State::Moving;

 public:
  Unit(int x, int y, int health, int damage,
       float attackCooldown, float attackRange, float movementSpeed,
       float visionRange, Player* owner, const std::string& name)
      : Entity(x, y, health, damage, attackCooldown, attackRange,
               owner),
        movementSpeed_(movementSpeed),
        visionRange_(visionRange),
        name_(name) {}
  void move(Direction dir, float dt);
  void moveToward(const sf::Vector2f& dest, float dt);

  std::pair<Entity*, sf::Vector2f> scanNearestEnemy(const std::vector<Entity*>& all) const;

  void drawVision(sf::RenderWindow& window, bool visible = true) const;

  void syncVisual();

  // std::string getName() const; //Debug
  virtual void update(float deltaTime) override;

  const std::string& getName() const { return name_; }  // Debug again

  void setStateAttacking();
  void setStateMoving();
  State getCurrentState() const;

  void setPath(const std::vector<sf::Vector2f>& newPath);

  void setTargetPosition(const sf::Vector2f& pos);

  void setTarget(Entity* target);
  Entity* getTarget() const;

  sf::Vector2f getLastTargetPoint() const;
    void setLastTargetPoint(const sf::Vector2f& point);

  // void heal(int amount); ?
};

#endif