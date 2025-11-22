#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

#include "Grid.hpp"
#include "Tile.hpp"

class Map {
 public:
  Map(int width, int height);

  const Tile& getTile(int x, int y) const;

  Grid& getGrid();
  const Grid& getGrid() const;

  void generateDefaultMap();

  // Maybe first random paths to connect king towers, then wave collapse
  // function to fill the rest?
  void generateRandomMap();

 private:
  Grid grid_;
};

#endif