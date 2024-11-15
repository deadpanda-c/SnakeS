cmake_minimum_required(VERSION 3.25)
project(binary_protocol)

set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall -Wextra -Wpedantic -Werror -fno-gnu-unique)

# Include directories
include_directories(./include)
set(SOURCES
    src/BinaryPacket.cpp
)

# Create the library target
add_library(binary_protocol STATIC ${SOURCES})
target_include_directories(binary_protocol PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
