cmake_minimum_required(VERSION 3.17)
project(GreenDots)

set(CMAKE_CXX_STANDARD 14)

add_executable(GreenDots src/main.cpp src/console.cpp src/console.hpp src/git.cpp src/git.hpp)