cmake_minimum_required(VERSION 3.25)
project(Snakes)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Options for exclusive builds
option(ONLY_CLIENT "Build only the Client program" OFF)
option(ONLY_SERVER "Build only the Server program" OFF)

# Ensure that only one of these options is enabled at a time
if(ONLY_CLIENT AND ONLY_SERVER)
    message(FATAL_ERROR "Cannot set both ONLY_CLIENT and ONLY_SERVER to ON.")
endif()

# Add subdirectory for the common library
add_subdirectory(libs/binary_protocol)

# Conditionally add Client and Server subdirectories
if(ONLY_CLIENT)
    add_subdirectory(Client)
elseif(ONLY_SERVER)
    add_subdirectory(Server)
else()
    # By default, build both if neither ONLY_CLIENT nor ONLY_SERVER is set
    add_subdirectory(Client)
    add_subdirectory(Server)
endif()
