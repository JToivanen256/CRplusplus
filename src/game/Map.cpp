#include "Map.hpp"
#include <cmath>
#include <queue>


Map::Map(int width, int height) : grid_(width, height) {}

Grid& Map::getGrid() { return grid_; }

const Grid& Map::getGrid() const { return grid_; }

void Map::generateDefaultMap() { grid_.defaultGridMap(); }

struct node {
  int row;
  int col;
  float gCost;
  float hCost;
  float fCost() const { return gCost + hCost; }
  node* parent = nullptr;
};

std::vector<sf::Vector2f> Map::findPath(sf::Vector2f& from, sf::Vector2f& to) {
}