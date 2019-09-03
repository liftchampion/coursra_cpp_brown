cmake_minimum_required(VERSION 3.14)
project(2_hash_set)

set(CMAKE_CXX_STANDARD 17)

include_directories(../dev)

add_executable(2_hash_set hash_set.cpp)