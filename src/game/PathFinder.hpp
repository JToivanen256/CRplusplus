#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include "Map.hpp"
#include <vector>

struct GridPosition {
  int x;
  int y;
};

class PathFinder {
public:
  std::vector<GridPosition> findPath(const GridPosition& start, const GridPosition& end) {}

private:
  const Map& map_;
};

#endif