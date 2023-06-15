cmake_minimum_required(VERSION 3.20)
project(compiler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE DEBUG)

file(GLOB_RECURSE sources src/*.cpp src/*.hpp)
add_executable(compiler ${sources})
