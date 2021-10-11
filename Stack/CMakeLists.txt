cmake_minimum_required(VERSION 3.16.3)


    project(Stack)

    set(CMAKE_CXX_STANDARD 14)

    add_executable(Stack main.cpp LibStack.cpp LibStack.h)


#if skek is library
#    project(LIB_STACK)
#
#    set(CMAKE_CXX_STANDARD 14)
#
#    set(SOURCE_LIB LibStack.cpp)
#
#    add_library(LibStack STATIC ${SOURCE_LIB})