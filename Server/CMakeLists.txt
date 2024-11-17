cmake_minimum_required(VERSION 3.16)

project(server VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})


include_directories("./include")

add_executable(server
    src/BinaryPacket.cpp
    src/Server.cpp
    src/GameLogic.cpp
    src/Snake.cpp
    src/main.cpp
)
target_link_libraries(server PRIVATE sfml-network sfml-system)

