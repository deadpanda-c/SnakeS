cmake_minimum_required(VERSION 3.10)
project(c_SnakeS)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall -Wextra -Wpedantic -Werror -fno-gnu-unique)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

find_library(LIBSFML_GRAPHICS sfml-graphics)
find_library(LIBSFML_WINDOW sfml-window)
find_library(LIBSFML_SYSTEM sfml-system)
find_library(LIBSFML_AUDIO sfml-audio)
find_library(LIBSFML_NETWORK sfml-network)

set(SOURCES
    src/main.cpp
    src/Core.cpp
    src/Tools.cpp
    src/Game.cpp
    src/Lobby.cpp
    src/Button.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${LIBSFML_GRAPHICS} ${LIBSFML_WINDOW} ${LIBSFML_SYSTEM} ${LIBSFML_AUDIO} ${LIBSFML_NETWORK})
