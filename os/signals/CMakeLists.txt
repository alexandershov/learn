cmake_minimum_required(VERSION 3.6)
project(signals)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.hpp)
add_executable(signals ${SOURCE_FILES})
