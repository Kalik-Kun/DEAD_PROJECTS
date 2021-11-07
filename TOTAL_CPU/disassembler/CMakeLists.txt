cmake_minimum_required(VERSION 3.20)

set(NAME_PROJECT disassembler)

project(${NAME_PROJECT})

set(CMAKE_CXX_STANDARD 23)

#set(STACK_DIR ../../Stack)
set(ONEGIN_DIR ../../Onegin)
set(HELP_DIR ../LibKalikHelp)

include_directories(${HELP_DIR})
include_directories(${ONEGIN_DIR})
include_directories(${STACK_DIR})

set(HEADERS_FILES  ${ONEGIN_DIR}/MyLibString.h ${HELP_DIR}/libHelpKalik.h)
set(CPP_FILES ${ONEGIN_DIR}/MyLibString.cpp ${HELP_DIR}/libHelpKalik.cpp)
set(SOURCE ${CPP_FILES} ${HEADERS_FILES})

set(OWN main.cpp Disassembler.cpp Disassembler.h)


add_executable(${NAME_PROJECT} ${OWN} ${SOURCE})
