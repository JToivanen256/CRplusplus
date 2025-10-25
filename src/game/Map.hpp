#ifndef MAP_HPP
#define MAP_HPP

#include "Tile.hpp"
#include <vector>

class Map {
public:
  Map(int width, int height);
  
  const Tile& getTile(int x, int y) const;

  void generateDefaultMap();

  // Maybe first random paths to connect king towers, then wave collapse function to fill the rest?
  void generateRandomMap();
  
private:
  int width_;
  int height_;
  std::vector<std::vector<Tile>> tiles_;
};

#endif