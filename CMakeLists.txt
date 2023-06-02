cmake_minimum_required(VERSION 3.25)
project(project)

set(CMAKE_CXX_STANDARD 17)

add_executable(project main.cpp code/Node.cpp code/Node.h code/Edge.cpp code/Edge.h code/Graph.cpp code/Graph.h code/Menu.cpp code/Menu.h)
