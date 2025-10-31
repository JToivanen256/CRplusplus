# ifndef ENTITY_HPP
# define ENTITY_HPP

#include <SFML/Graphics.hpp>

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
  float attackCooldown_;
  float attackRange_;
  bool isAlive_ = true;
  sf::Sprite sprite_;
  sf::Texture texture_;


public:
  Entity(int x, int y, int gridX, int gridY, int health, int damage, float attackCooldown, float attackRange)
    : position_{x, y}, gridPosition_{gridX, gridY}, health_(health), damage_(damage),
      attackCooldown_(attackCooldown), attackRange_(attackRange) {}

  virtual ~Entity() = default;

  GridPos getGridPosition() const;
  Pos getPosition() const;

  virtual void attack() = 0;

  virtual void update() = 0;

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