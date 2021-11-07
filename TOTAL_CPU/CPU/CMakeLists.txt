cmake_minimum_required(VERSION 3.20)

set(NAME_PROJECT CPU)

project(${NAME_PROJECT})

set(CMAKE_CXX_STANDARD 23)

set(STACK_DIR ../../Stack)
set(ONEGIN_DIR ../../Onegin)
set(HELP_DIR ../LibKalikHelp)

include_directories(${HELP_DIR})
include_directories(${ONEGIN_DIR})
include_directories(${STACK_DIR})

set(HEADERS_FILES ${STACK_DIR}/LibStack.h ${ONEGIN_DIR}/MyLibString.h ${HELP_DIR}/libHelpKalik.h)
set(CPP_FILES ${STACK_DIR}/LibStack.cpp ${ONEGIN_DIR}/MyLibString.cpp ${HELP_DIR}/libHelpKalik.cpp)
set(SOURCE ${CPP_FILES} ${HEADERS_FILES})

set(OWN main.cpp LibProc.cpp LibProc.h)

#find_library(LIB_TO_INCLUDE KalikHelp ../LibKalikHelp/cmake-build-debug)

add_executable(${NAME_PROJECT} ${OWN} ${SOURCE})
