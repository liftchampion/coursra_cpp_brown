cmake_minimum_required(VERSION 3.14)
project(09_ini)

set(CMAKE_CXX_STANDARD 17)

include_directories(../dev)

add_executable(09_ini test_ini.cpp ini.h)