cmake_minimum_required(VERSION 3.6)
project(pearls)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(pearls)

add_subdirectory(tests)
add_subdirectory(pearls)
