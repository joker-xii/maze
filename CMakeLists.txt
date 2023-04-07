cmake_minimum_required(VERSION 3.16)
project(game_ds)

set(CMAKE_CXX_STANDARD 17)

add_executable(game_ds disjoint_set.h maze.h main.cpp)