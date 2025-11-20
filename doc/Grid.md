# Grid class — quick reference

## Overview
- 2D grid stored in a 1D vector (row-major).
- index = row * columns + col.
- Default tile size = `13` (member `tileSize`).

## TileFlag (enum)
- `TileFlag::Grass` — normal ground.
- `TileFlag::Water` — water tile.
- `TileFlag::Bridge` — bridge tile.

## Tile (struct) — fields
- `sf::RectangleShape shape` — visual rectangle for the tile.
- `bool walkable` — can units/pathfinding enter this tile?
- `float cost` — movement cost multiplier.
- `std::vector<int> occupants` — list of unit IDs on the tile (allows multiple units).
- `TileFlag flag` — logical type set by `defaultGridMap`.

## Grid members
- `int tileSize` — pixel size for each tile.
- `int columns, rows` — grid dimensions.
- `std::vector<Tile> tiles` — storage for all tiles.

## Constructor
- `Grid(int xSize, int ySize)`  
  - Initializes `columns = xSize`, `rows = ySize`, creates and positions tiles.

## Drawing & map setup
- `void draw(sf::RenderWindow& window)` — draws each tile.
- `void defaultGridMap()` — assigns colors, `walkable`, `cost`, and `flag`:
  - Bridge tiles: set to Bridge flag.
  - Water tiles: set to Water flag.
  - Grass tiles: set to Grass flag.

## Accessors / helpers
- `int getColumns() const`
- `int getRows() const`
- `int getTileSize() const`
- `Tile& at(int row, int col)` / `const Tile& at(...) const` — access tile.
- `bool inBounds(int row, int col) const` — true if inside grid.
- `int toIndex(int row, int col) const` — row-major index.

## Occupancy API
- `void addOccupant(int row, int col, int unitId)` — add unit id (no dupes).
- `void removeOccupant(int row, int col, int unitId)` — remove unit id.
- `const std::vector<int>& getOccupants(int row, int col) const` — occupant list (or empty if OOB).
- `bool isOccupied(int row, int col) const` — true if occupants list not empty.

## Neighbors (for pathfinding)
- `std::vector<std::pair<int,int>> getNeighbors(int row, int col, bool diagonals = false) const`  
  - Returns valid neighbor (row,col) pairs inside bounds.
  - `diagonals = false` → 4-way (N,S,E,W).  
  - `diagonals = true` → 8-way (includes diagonals).

## Usage notes
- Pathfinding: use `getNeighbors` + `at(...).walkable` + `at(...).cost`. Optionally skip tiles where `isOccupied` is true.
- Units: call `addOccupant` when entering a tile and `removeOccupant` when leaving.
- If occupant ops become a bottleneck, replace `std::vector<int>` with `std::unordered_set<int>` for O(1) remove/find.