cmake_minimum_required(VERSION 3.17)
project(Onegin C)

set(CMAKE_C_STANDARD 99)

add_executable(Onegin main.cpp onegin_func.cpp onegin_func.h main.cpp)