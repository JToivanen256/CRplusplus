#include <gtest/gtest.h>
#include "../src/game/Grid.hpp"

TEST(GridTest, InitializeGrid) {
  Grid grid(5, 5);
  EXPECT_EQ(grid.getRows(), 5);
  EXPECT_EQ(grid.getColumns(), 5);
}

TEST(GridTest, InBounds) {
  Grid grid(5, 5);
  EXPECT_TRUE(grid.inBounds(0, 0));
  EXPECT_TRUE(grid.inBounds(4, 4));
  EXPECT_FALSE(grid.inBounds(-1, 0));
  EXPECT_FALSE(grid.inBounds(0, 5));
}

TEST(GridTest, gridToWorld) {
  Grid grid(5, 5);
  auto pos = grid.gridToWorld(2, 3);
  EXPECT_EQ(pos.x, 3 * grid.getTileSize() + grid.getTileSize() * 0.5f);
  EXPECT_EQ(pos.y, 2 * grid.getTileSize() + grid.getTileSize() * 0.5f);
}

TEST(GridTest, WorldToGrid) {
  Grid grid(5, 5);
  sf::Vector2f worldPos(45.f, 26.f); // Assuming tileSize is 13
  auto [row, col] = grid.worldToGrid(worldPos);
  EXPECT_EQ(row, 2);
  EXPECT_EQ(col, 3);
}