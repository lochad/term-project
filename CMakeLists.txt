cmake_minimum_required(VERSION 3.16)
project(KDTreeProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

# Source files for the library (if you have any separate implementation)
set(KDTREE_LIB_SOURCES
    # If you have a separate kdtree.cpp, list it here:
    code/kdtree.cpp 
)

# Create a library for the KD-tree code
add_library(kdtree_lib ${KDTREE_LIB_SOURCES})

# Executable for your main application
add_executable(run_app app/main.cpp)
target_link_libraries(run_app kdtree_lib)

# Testing (using Google Test - optional)
find_package(GTest QUIET)
if(GTEST_FOUND)
    include_directories(${GTEST_INCLUDE_DIRS})
else()
    message(STATUS "Google Test not found. Tests will not be built.")
endif()