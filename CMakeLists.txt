cmake_minimum_required(VERSION 3.10)
project(strategy-game-1)

# Find SFML package (you can adjust the version as needed)
find_package(SFML 2.5 REQUIRED graphics window system)


file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS src/*.cpp src/*/*.cpp)
add_executable(strategy-game-1 ${PROJECT_SOURCES})

add_custom_command(TARGET strategy-game-1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:strategy-game-1>/assets)

    
# Link the necessary SFML libraries
target_link_libraries(strategy-game-1 sfml-graphics sfml-window sfml-system)