cmake_minimum_required(VERSION 3.15)
project(CrossPlatformSFMLApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Detect platform and set SFML root ---
if(WIN32)
    set(SFML_ROOT "${CMAKE_SOURCE_DIR}/sfml/Windows/SFML-3.0.2")
elseif(APPLE)
    set(SFML_ROOT "${CMAKE_SOURCE_DIR}/sfml/Mac/SFML-3.0.2")
elseif(UNIX)
    set(SFML_ROOT "${CMAKE_SOURCE_DIR}/sfml/Linux/SFML-3.0.2")
else()
    message(FATAL_ERROR "Unsupported platform!")
endif()

# --- Use the SFML CMake package if available ---
set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

# --- Collect sources ---
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Window SFML::System)
target_include_directories(${PROJECT_NAME} PRIVATE "${SFML_ROOT}/include")

# --- Windows: Copy matching SFML DLLs after build ---
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying SFML DLLs for $<CONFIG> build..."
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<$<CONFIG:Debug>:${SFML_ROOT}/bin/sfml-graphics-d-3.dll>"
            "$<$<CONFIG:Release>:${SFML_ROOT}/bin/sfml-graphics-3.dll>"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<$<CONFIG:Debug>:${SFML_ROOT}/bin/sfml-window-d-3.dll>"
            "$<$<CONFIG:Release>:${SFML_ROOT}/bin/sfml-window-3.dll>"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<$<CONFIG:Debug>:${SFML_ROOT}/bin/sfml-system-d-3.dll>"
            "$<$<CONFIG:Release>:${SFML_ROOT}/bin/sfml-system-3.dll>"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        # Optional additional SFML components
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<$<CONFIG:Debug>:${SFML_ROOT}/bin/sfml-audio-d-3.dll>"
            "$<$<CONFIG:Release>:${SFML_ROOT}/bin/sfml-audio-3.dll>"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<$<CONFIG:Debug>:${SFML_ROOT}/bin/sfml-network-d-3.dll>"
            "$<$<CONFIG:Release>:${SFML_ROOT}/bin/sfml-network-3.dll>"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    )
endif()

# --- macOS/Linux: Set runtime paths ---
if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        BUILD_RPATH "@executable_path/../lib"
    )
elseif(UNIX AND NOT APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        BUILD_RPATH "$ORIGIN/../lib"
    )
endif()

# --- MSVC runtime consistency ---
if(MSVC)
    # Use dynamic runtime library (matches SFML binaries)
    set_property(TARGET ${PROJECT_NAME} PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
    )
endif()

# --- Optional: nice grouping in IDEs ---
source_group(TREE "${CMAKE_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${SOURCES})
