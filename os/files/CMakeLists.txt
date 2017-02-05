cmake_minimum_required(VERSION 3.5)

project(files)

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.hpp)

add_executable(files ${SOURCE_FILES})
