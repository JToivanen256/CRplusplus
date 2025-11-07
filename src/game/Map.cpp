#include "Map.hpp"


Map::Map(int width, int height)
  : grid_(width, height) {}

Grid& Map::getGrid() {
    return grid_;
}



