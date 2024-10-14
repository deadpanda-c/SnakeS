cmake_minimum_required(VERSION 3.10)
project(c_SnakeS)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-Wall -Wextra -Wpedantic -Werror -fno-gnu-unique)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

find_library(LIBSFML_GRAPHICS sfml-graphics)
find_library(LIBSFML_WINDOW sfml-window)
find_library(LIBSFML_SYSTEM sfml-system)

# Include directories
set(SOURCES
    src/main.cpp
    src/Core.cpp
    src/Graphics.cpp
)

# Create the executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Link the libraries
target_link_libraries(${PROJECT_NAME} ${LIBSFML_GRAPHICS} ${LIBSFML_WINDOW} ${LIBSFML_SYSTEM})
