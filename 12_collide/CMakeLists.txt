cmake_minimum_required(VERSION 3.14)
project(12_collide)

set(CMAKE_CXX_STANDARD 17)

include_directories(../dev)

add_executable(12_collide collide.cpp geo2d.cpp game_object.h geo2d.h)