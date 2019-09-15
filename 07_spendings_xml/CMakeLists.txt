cmake_minimum_required(VERSION 3.14)
project(07_spendings_xml)

set(CMAKE_CXX_STANDARD 17)

include_directories(../dev)

add_executable(07_spendings_xml spendings_xml.cpp xml.cpp xml.h)