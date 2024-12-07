cmake_minimum_required(VERSION 3.22)
project(client_communication)

set(CMAKE_CXX_STANDARD 20)
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE SAMPLE "sample/main.cpp")
include_directories(include)

add_library(client_communication SHARED ${SOURCES})
add_executable(sample ${SAMPLE})
target_link_libraries(sample client_communication)
