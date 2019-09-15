cmake_minimum_required(VERSION 3.14)
project(08_spendings_json)

set(CMAKE_CXX_STANDARD 17)

include_directories(../dev)

add_executable(08_spendings_json json.cpp json.h spendings_json.cpp)