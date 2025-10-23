cmake_minimum_required(VERSION 3.10)
project(strategy-game-1)

# Find SFML package (you can adjust the version as needed)
find_package(SFML 2.5 REQUIRED graphics window system)

add_executable(strategy-game-1 src/main.cpp)

# Link the necessary SFML libraries
target_link_libraries(strategy-game-1 sfml-graphics sfml-window sfml-system)
