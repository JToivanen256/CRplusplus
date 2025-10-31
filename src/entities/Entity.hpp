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
  sf::Sprite sprite_;
  sf::Texture texture_;


public:
  Entity(int x, int y, int gridX, int gridY) : position_{x, y}, gridPosition_{gridX, gridY} {}
  virtual ~Entity() = default;

  GridPos getGridPosition() const;
  Pos getPosition() const;

  virtual void update() = 0;

  void draw(sf::RenderWindow& window) {
    window.draw(sprite_);
  }

};

# endif 