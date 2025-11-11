# ifndef ENTITY_HPP
# define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "../players/Player.hpp"

struct GridPos {
  int x;
  int y;
};

struct Pos {
  int x;
  int y;
};


class Entity {
protected:
  GridPos gridPosition_;
  Pos position_;
  int health_;
  int damage_;
  float currentCooldown_ = 0.0f;
  float attackCooldown_;
  float attackRange_;
  bool isAlive_ = true;
  sf::Sprite sprite_;
  sf::Texture texture_;
  Player* owner_;


public:
  Entity(int x, int y, int gridX, int gridY, int health, int damage, float attackCooldown, float attackRange, Player* owner)
    : position_{x, y}, gridPosition_{gridX, gridY}, health_(health), damage_(damage),
      attackCooldown_(attackCooldown), attackRange_(attackRange), owner_(owner){}

  virtual ~Entity() = default;

  GridPos getGridPosition() const;
  Pos getPosition() const;

  // Can attack only if not on cooldown, Combat class should handle combat and ask if units aren't on cooldown
  bool canAttack() const {
    return currentCooldown_ <= 0.0f;
  };

  Player* getOwner()const{
    return owner_;
  } 

  virtual void attack(Entity& target) { 
      target.takeDamage(damage_);
      currentCooldown_ = attackCooldown_;
  }

  virtual void update(float deltaTime) = 0;

  void takeDamage(int amount) {
    health_ -= amount;
    if (health_ <= 0) {
      isAlive_ = false;
    }
  }

  bool isDead() const {
    return !isAlive_;
  }

  void draw(sf::RenderWindow& window) {
    window.draw(sprite_);
  }

};

# endif 