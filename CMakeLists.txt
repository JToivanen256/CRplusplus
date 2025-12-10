cmake_minimum_required(VERSION 3.10)
project(strategy-game-1)

# Force C++17 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML package (you can adjust the version as needed)
find_package(SFML 2.5 REQUIRED graphics window system)


file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS src/*.cpp src/*/*.cpp)

set(MAIN_SRC ${CMAKE_SOURCE_DIR}/src/main.cpp)
list(REMOVE_ITEM PROJECT_SOURCES ${MAIN_SRC})

add_library(game_lib STATIC ${PROJECT_SOURCES})
target_include_directories(game_lib PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(game_lib PUBLIC sfml-graphics sfml-window sfml-system)

add_executable(strategy-game-1 ${MAIN_SRC})
target_link_libraries(strategy-game-1 PRIVATE game_lib)

add_custom_command(TARGET strategy-game-1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:strategy-game-1>/assets)

if(EXISTS "${CMAKE_SOURCE_DIR}/tests/CMakeLists.txt")
  add_subdirectory(tests)
endif()