cmake_minimum_required(VERSION 3.14)
project(05_hash_person)

set(CMAKE_CXX_STANDARD 17)
include_directories(../dev)

add_executable(05_hash_person hash_person.cpp)