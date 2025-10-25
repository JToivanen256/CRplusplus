#ifndef TILE_HPP
#define TILE_HPP

class Tile {
public:
  enum class Type { Grass, Water, Frozen, Poisoned };

  Tile(Type type) : type_(type) {}

  Type getType() const;

private:
  Type type_;
};

#endif