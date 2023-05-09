cmake_minimum_required(VERSION 3.25)
project(project)

set(CMAKE_CXX_STANDARD 17)

add_executable(project main.cpp Node.cpp Node.h Edge.cpp Edge.h Graph.cpp Graph.h)
