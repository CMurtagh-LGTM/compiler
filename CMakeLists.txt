cmake_minimum_required(VERSION 3.20)
project(compiler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE sources src/*.cpp src/*.hpp)
add_executable(compiler ${sources})

target_include_directories(compiler PRIVATE src/)

add_custom_target(
        clangformat
        COMMAND /usr/bin/clang-format
        -i
        ${sources}
)
