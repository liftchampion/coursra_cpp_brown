cmake_minimum_required(VERSION 3.14)
project(10_refactoring)

set(CMAKE_CXX_STANDARD 17)

include_directories(../dev)

add_executable(10_refactoring json.cpp refactoring.cpp xml.cpp
                json.h xml.h )