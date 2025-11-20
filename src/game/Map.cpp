#include "Map.hpp"


Map::Map(int width, int height)
  : grid_(width, height) {}

Grid& Map::getGrid() {
    return grid_;
}

void Map::generateDefaultMap()
{
  grid_.defaultGridMap();
}

