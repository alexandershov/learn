cmake_minimum_required(VERSION 3.6)
project(clrs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(insort STATIC src/lib/ch2/insort.cpp)
add_executable(clrs main.cpp)
target_link_libraries(clrs insort)
