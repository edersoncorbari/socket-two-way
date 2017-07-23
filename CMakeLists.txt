cmake_minimum_required(VERSION 2.8.11)
project(socket-two-way)

add_definitions(-DLIB_NAME="Socket-Two-Way")
add_definitions(-DLIB_VERSION="1.0.0")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -g -std=c++14")

add_subdirectory(socket-two-way)
add_subdirectory(tools)

