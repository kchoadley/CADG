# Basic CMake project
cmake_minimum_required(VERSION 3.10.2) # latest release as of 10/23/2018

# Set project name
project(CADG)

# Set source files
set(CADG_SOURCES
    example.cpp)

# Set C++17 as the standard
set(CMAKE_CXX_STANDARD 17)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests ${CADG_SOURCES})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread fruit)
