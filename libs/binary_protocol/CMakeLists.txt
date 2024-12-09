cmake_minimum_required(VERSION 3.22)

project(communications)

file(GLOB_RECURSE SOURCES src/*.cpp)

include_directories(./include)

add_library(communications SHARED ${SOURCES})

# add_executable(sample main.cpp)
target_link_libraries(sample communications)
