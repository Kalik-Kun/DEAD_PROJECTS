# Задать 3.20 минимальную версию CMake
cmake_minimum_required(VERSION 3.20)

# Задать характеристики проекта "assembler":
project(assembler VERSION 0.1)
#project(assembler)

## Запустить скрипт `CMakeLists.cmake` на выполнение:
#include(../Stack/CMakeLists.txt)



set(CMAKE_CXX_STANDARD 23)

include_directories(../Stack)
#install(FILES prog.txt DESTINATION Stack)
#install(DIRECTORY ../Stack DESTINATION cmake-build-debug/)

add_executable(assembler main.cpp Assembler.h Assembler.cpp)

add_subdirectory(../Stack Stack)

target_link_libraries(assembler ../Stack/cmake-build-debug/libLibStack.a)
# Добавить каталог "../Stack" в сборку основного проекта,
# а генерируемые файлы расположить в каталоге "../Stack/cmake-build-debug":
#add_subdirectory(../Stack ../Stack)



