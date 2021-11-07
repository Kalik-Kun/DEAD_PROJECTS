# Задать 3.20 минимальную версию CMake
cmake_minimum_required(VERSION 3.20)

# Задать характеристики проекта "assembler":
#project(assembler VERSION 0.1)
#project(assembler)

## Запустить скрипт `CMakeLists.cmake` на выполнение:
#include(../Stack/CMakeLists.txt)


set(NAME_PROJECT assembler)

project(${NAME_PROJECT})

set(CMAKE_CXX_STANDARD 23)

set(STACK_DIR ../../Stack)
set(ONEGIN_DIR ../../Onegin)
set(HELP_DIR ../LibKalikHelp)

include_directories(${HELP_DIR})
include_directories(${ONEGIN_DIR})
include_directories(${STACK_DIR})

#${STACK_DIR}/LibStack.h
#${STACK_DIR}/LibStack.cpp
set(HEADERS_FILES ${ONEGIN_DIR}/MyLibString.h ${STACK_DIR}/LibStack.h ${HELP_DIR}/libHelpKalik.h)
set(CPP_FILES ${ONEGIN_DIR}/MyLibString.cpp ${STACK_DIR}/LibStack.cpp ${HELP_DIR}/libHelpKalik.cpp)
set(SOURCE ${CPP_FILES} ${HEADERS_FILES})

set(OWN main.cpp Assembler.cpp Assembler.h)

add_executable(${NAME_PROJECT} ${OWN} ${SOURCE})

#install(FILES prog.txt DESTINATION Stack)
#install(DIRECTORY ../Stack DESTINATION cmake-build-debug/)

#add_executable(assembler main.cpp Assembler.h Assembler.cpp ../Stack/LibStack.cpp ../Onegin/MyLibString.cpp ../LibKalikHelp/libHelpKalik.cpp)
#add_subdirectory(../Stack Stack)
#
#target_link_libraries(assembler ../Stack/cmake-build-debug/libLibStack.a)
# Добавить каталог "../Stack" в сборку основного проекта,
# а генерируемые файлы расположить в каталоге "../Stack/cmake-build-debug":
#add_subdirectory(../Stack ../Stack)



