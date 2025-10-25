# ifndef ENTITY_HPP
# define ENTITY_HPP

struct GridPos {
  int x;
  int y;
};


class Entity {
protected:
  GridPos position_;
  // sf::Sprite sprite;? 


public:
  Entity(int x, int y) : position_{x, y} {}
  virtual ~Entity() = default;

  GridPos getPosition() const;

  virtual void update() = 0;

};

# endif 