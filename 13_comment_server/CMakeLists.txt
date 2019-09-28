cmake_minimum_required(VERSION 3.14)
project(13_comment_server)

set(CMAKE_CXX_STANDARD 17)

include_directories(../dev)

add_executable(13_comment_server comment_server.cpp)