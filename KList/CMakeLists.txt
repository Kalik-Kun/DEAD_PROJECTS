cmake_minimum_required(VERSION 3.20)
project(KList)

set(CMAKE_CXX_STANDARD 23)

add_executable(KList main.cpp KList.cpp KList.h KList_impl.h)
