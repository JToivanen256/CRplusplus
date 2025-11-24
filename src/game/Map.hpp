#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <SFML/Graphics.hpp>

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

  std::vector<sf::Vector2f> findPath(sf::Vector2f& from, sf::Vector2f& to);

 private:
  Grid grid_;
};

#endif