cmake_minimum_required(VERSION 3.20)

set (NAME_PROJECT DIF)
set (CMAKE_CXX_STANDARD 23)

project(${NAME_PROJECT})

set(DIR_ONEGIN ../Onegin)

include_directories(${DIR_ONEGIN})

set(OWN_HEADERS DF_Headers/KTree.h DF_Headers/KLexer.h DF_Headers/KDump.h DF_Headers/DF_define_operation.h DF_Headers/Oper_Name.h)
set(OWN_CPP DF_Source/KTree.cpp DF_Source/KLexer.cpp DF_Source/KDump.cpp)
set(OWN ${OWN_HEADERS} ${OWN_CPP})

set(ALIEN_HEADERS ${DIR_ONEGIN}/MyLibString.h)
set(ALIEN_CPP ${DIR_ONEGIN}/MyLibString.cpp)
set(ALIEN ${ALIEN_HEADERS} ${ALIEN_CPP})

add_executable(${NAME_PROJECT} ${OWN} ${ALIEN})
