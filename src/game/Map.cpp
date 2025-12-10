#include "Map.hpp"

#include <cmath>
#include <iostream>
#include <queue>

Map::Map(int width, int height) : grid_(width, height) {}

Grid& Map::getGrid() { return grid_; }

const Grid& Map::getGrid() const { return grid_; }

void Map::generateDefaultMap() { grid_.defaultGridMap(); }

// node structure for A* pathfinding
struct node {
  int row;
  int col;
  float gCost;
  float hCost;
  float fCost() const { return gCost + hCost; }
  node* parent = nullptr;
};

// A* pathfinding
std::vector<sf::Vector2f> Map::findPath(sf::Vector2f& from, sf::Vector2f& to) {
  auto [startRow, startCol] = grid_.worldToGrid(from);
  auto [goalRow, goalCol] = grid_.worldToGrid(to);

  const int rows = grid_.getRows();
  const int cols = grid_.getColumns();

  if (startRow < 0 || startCol < 0 || goalRow < 0 || goalCol < 0 ||
      startRow >= rows || startCol >= cols || goalRow >= rows ||
      goalCol >= cols) {
    std::cout << "Start or goal out of bounds!\n";
    return {};
  }
  if (startRow == goalRow && startCol == goalCol) {
    return {grid_.gridToWorld(startRow, startCol)};
  }

  // Calvculate heuristic (octile distance)
  auto heuristic = [&](int r, int c) {
    int dx = std::abs(r - goalRow);
    int dy = std::abs(c - goalCol);
    const float D = 1.0f;
    const float D2 = 1.41421356237f;

    return (D * (dx + dy) + (D2 - 2.0f * D) * std::min(dx, dy));
  };

  // Initialize nodes
  std::vector<std::vector<node>> nodes(rows, std::vector<node>(cols));
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      nodes[r][c].row = r;
      nodes[r][c].col = c;
      nodes[r][c].gCost = std::numeric_limits<float>::infinity();
      nodes[r][c].hCost = heuristic(r, c);
      nodes[r][c].parent = nullptr;
    }
  }

  // Comparator for priority queue
  auto cmp = [&](node* a, node* b) {
    float fA = a->fCost();
    float fB = b->fCost();

    if (std::abs(fA - fB) < 0.0001f) {
      return a->hCost > b->hCost;
    }
    return fA > fB;
  };

  // Priority queue for open list
  std::priority_queue<node*, std::vector<node*>, decltype(cmp)> openList(cmp);

  // Start from the starting node
  node* startNode = &nodes[startRow][startCol];
  startNode->gCost = 0.f;
  openList.push(startNode);

  // Closed set to track visited nodes
  std::vector<std::vector<char>> closedSet(rows, std::vector<char>(cols, 0));
  node* goalNode = nullptr;

  // A* main loop
  while (!openList.empty()) {
    node* current = openList.top();
    openList.pop();

    if (closedSet[current->row][current->col]) continue;
    closedSet[current->row][current->col] = 1;

    if (current->row == goalRow && current->col == goalCol) {
      goalNode = current;
      break;
    }

    // Explore neighbors
    for (auto nb : grid_.getNeighbors(current->row, current->col, true)) {
      int nr = nb.first;
      int nc = nb.second;

      if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
      if (!grid_.at(nr, nc).walkable) continue;

      if (closedSet[nr][nc]) continue;
      if (grid_.isOccupied(nr, nc) && !(nr == goalRow && nc == goalCol)) {
        continue;
      }

      // Determine movement cost
      int dr = std::abs(nr - current->row);
      int dc = std::abs(nc - current->col);
      const float stepCost = (dr == 1 && dc == 1) ? 1.41421356237f : 1.0f;

      // Tentative g cost
      float tentativeG = current->gCost + stepCost;
      node* neighbour = &nodes[nr][nc];

      if (tentativeG < neighbour->gCost) {
        neighbour->gCost = tentativeG;
        neighbour->parent = current;
        openList.push(neighbour);
      }
    }
  }

  std::vector<sf::Vector2f> path;
  if (!goalNode) {
    // std::cout << "No path found!\n";
    return path;
  }

  // Reconstruct path
  for (node* cur = goalNode; cur != nullptr; cur = cur->parent)
    path.push_back(grid_.gridToWorld(cur->row, cur->col));
  std::reverse(path.begin(), path.end());
  return path;
}