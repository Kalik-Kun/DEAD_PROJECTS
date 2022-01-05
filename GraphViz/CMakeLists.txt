cmake_minimum_required(VERSION 3.20)
project(GraphViz)

set(CMAKE_CXX_STANDARD 23)

add_executable(GraphViz main.cpp KLibGraphV.cpp KLibGraphV.h)
