#include <gtest/gtest.h>
#include "../src/game/Map.hpp"

TEST(MapTest, InitializeMap) {
  Map map(5, 5);
  EXPECT_EQ(map.getGrid().getRows(), 5);
  EXPECT_EQ(map.getGrid().getColumns(), 5);
}

TEST(MapTest, FindPathEmptyGrid) {
  Map map(30, 50);
  map.generateDefaultMap();
  sf::Vector2f start(10.0f, 10.0f); // just some path accross the map
  sf::Vector2f goal(300.0f, 500.0f);
  auto path = map.findPath(start, goal);

  EXPECT_FALSE(path.empty());

  const float eps = 10.0f;
  EXPECT_NEAR(path.front().x, start.x, eps);
  EXPECT_NEAR(path.front().y, start.y, eps);
  EXPECT_NEAR(path.back().x, goal.x, eps);
  EXPECT_NEAR(path.back().y, goal.y, eps);
}