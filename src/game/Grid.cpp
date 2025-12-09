#include "Grid.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

Grid::Grid(int xSize, int ySize)
    : columns(xSize), rows(ySize), tiles(xSize * ySize) {
  for (int row = 0; row < rows; row++) {
    for (int column = 0; column < columns; column++) {
      auto& t = tiles[row * columns + column];
      t.shape.setSize(sf::Vector2f(static_cast<float>(tileSize),
                                   static_cast<float>(tileSize)));
      t.shape.setPosition(static_cast<float>(column) * tileSize,
                          static_cast<float>(row) * tileSize);
      t.shape.setOutlineThickness(1.f);
      t.shape.setOutlineColor(sf::Color::Black);
      t.walkable = true;
      t.cost = 1.f;
      t.occupants.clear();
      t.flag = TileFlag::Grass;
    }
  }
}

Grid::Tile& Grid::at(int row, int col) { return tiles[row * columns + col]; }

const Grid::Tile& Grid::at(int row, int col) const {
  return tiles[row * columns + col];
}

int Grid::getColumns() const { return columns; }
int Grid::getRows() const { return rows; }
int Grid::getTileSize() const { return tileSize; }

bool Grid::inBounds(int row, int col) const {
  return row >= 0 && row < rows && col >= 0 && col < columns;
}

int Grid::toIndex(int row, int col) const { return row * columns + col; }

std::pair<int, int> Grid::worldToGrid(const sf::Vector2f& worldPos) const {
  int col = static_cast<int>(worldPos.x) / tileSize;
  int row = static_cast<int>(worldPos.y) / tileSize;
  return {row, col};
}

sf::Vector2f Grid::gridToWorld(int row, int col) const {
  return sf::Vector2f(static_cast<float>(col * tileSize) + tileSize * 0.5f,
                      static_cast<float>(row * tileSize) + tileSize * 0.5f);
}

sf::Vector2f Grid::gridToWorldCenter(int row, int col) const {
  auto topLeft = gridToWorld(row, col);
  return topLeft + sf::Vector2f(tileSize * 0.5f, tileSize * 0.5f);
}

void Grid::addOccupant(int row, int col, int unitId) {
  if (!inBounds(row, col)) return;
  auto& occ = tiles[toIndex(row, col)].occupants;
  if (std::find(occ.begin(), occ.end(), unitId) == occ.end())
    occ.push_back(unitId);
}

void Grid::removeOccupant(int row, int col, int unitId) {
  if (!inBounds(row, col)) return;
  auto& occ = tiles[toIndex(row, col)].occupants;
  auto it = std::find(occ.begin(), occ.end(), unitId);
  if (it != occ.end()) occ.erase(it);
}

const std::vector<int>& Grid::getOccupants(int row, int col) const {
  static const std::vector<int> empty;
  if (!inBounds(row, col)) return empty;
  return tiles[toIndex(row, col)].occupants;
}

bool Grid::isOccupied(int row, int col) const {
  if (!inBounds(row, col)) return false;
  return !tiles[toIndex(row, col)].occupants.empty();
}

std::vector<std::pair<int, int>> Grid::getNeighbors(int row, int col,
                                                    bool diagonals) const {
  // Multidimensional arrays for both diagonal checking and non-diagonal chcking
  static const int d4[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  static const int d8[8][2] = {{-1, 0},  {1, 0},  {0, -1}, {0, 1},
                               {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

  std::vector<std::pair<int, int>> out;
  if (diagonals) {
    for (auto& d : d8) {
      int r = row + d[0], c = col + d[1];
      if (inBounds(r, c)) out.emplace_back(r, c);
    }
  } else {
    for (auto& d : d4) {
      int r = row + d[0], c = col + d[1];
      if (inBounds(r, c)) out.emplace_back(r, c);
    }
  }
  return out;
}

void Grid::draw(sf::RenderWindow& window) {
  for (auto& t : tiles) {
    window.draw(t.shape);
  }
}
bool Grid::loadFromFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    return false;
  }

  int fileColumns, fileRows;
  file >> fileColumns >> fileRows;

  if (fileColumns != columns || fileRows != rows) {
    file.close();
    return false;
  }

  std::string line;
  std::getline(file, line);

  for (int row = 0; row < rows; row++) {
    if (!std::getline(file, line)) {
      file.close();
      return false;
    }

    for (int col = 0; col < columns && col < static_cast<int>(line.length());
         col++) {
      auto& t = tiles[row * columns + col];
      char tileChar = line[col];

      switch (tileChar) {
        case 'G':  // Grass
          t.shape.setFillColor(sf::Color::Green);
          t.walkable = true;
          t.cost = 1.f;
          t.flag = TileFlag::Grass;
          break;
        case 'W':  // Water
          t.shape.setFillColor(sf::Color(0, 153, 255));
          t.walkable = false;
          t.cost = 1.f;
          t.flag = TileFlag::Water;
          break;
        case 'B':  // Bridge
          t.shape.setFillColor(sf::Color(210, 105, 30));
          t.walkable = true;
          t.cost = 1.f;
          t.flag = TileFlag::Bridge;
          break;
        default:
          t.shape.setFillColor(sf::Color::Green);
          t.walkable = true;
          t.cost = 1.f;
          t.flag = TileFlag::Grass;
          break;
      }
    }
  }

  file.close();
  return true;
}

void Grid::defaultGridMap() {
  static const std::filesystem::path projectRoot =
      std::filesystem::path(__FILE__).parent_path().parent_path().parent_path();
  const auto mapPath = projectRoot / "defaultMap.txt";

  if (loadFromFile(mapPath.string())) {
    std::cout << "Could read the file! YEY!" << std::endl;
    return;
  }

  // If can't read from file then use the default map
  std::cout << "Could not load map file, using default map written in code"
            << std::endl;

  for (int row = 0; row < rows; row++) {
    for (int column = 0; column < columns; column++) {
      auto& t = tiles[row * columns + column];
      if (row == (rows / 2) || row == ((rows / 2) - 1) ||
          row == ((rows / 2) - 2) || row == ((rows / 2) + 1)) {
        if (column == (columns / 4) || column == ((columns / 4) + 1) ||
            column == (((columns / 4) * 3)) ||
            column == ((((columns / 4) * 3) + 1))) {
          t.shape.setFillColor(sf::Color(210, 105, 30));
          t.walkable = true;
          t.flag = TileFlag::Bridge;
        } else {
          t.shape.setFillColor(sf::Color(0, 153, 255));
          t.walkable = false;
          t.cost = 1.f;
          t.flag = TileFlag::Water;
        }
      } else {
        t.shape.setFillColor(sf::Color::Green);
        t.walkable = true;
        t.cost = 1.f;
        t.flag = TileFlag::Grass;
      }
    }
  }
}
