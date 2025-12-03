include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/tests/*.cpp")
add_executable(test_core ${TEST_SOURCES})
target_include_directories(test_core PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test_core PRIVATE gtest_main game_lib)

add_test(NAME core_tests COMMAND test_core)