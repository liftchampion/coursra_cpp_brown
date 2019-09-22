cmake_minimum_required(VERSION 3.14)
project(11_restructing)

set(CMAKE_CXX_STANDARD 17)

include_directories(../dev)

add_executable(11_restructing main.cpp stats_aggregator.cpp stats_aggregator_test.cpp
        stats_aggregator.h)