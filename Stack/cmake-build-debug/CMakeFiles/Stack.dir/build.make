# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/178/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/178/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Stack

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Stack/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Stack.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Stack.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Stack.dir/flags.make

CMakeFiles/Stack.dir/main.cpp.o: CMakeFiles/Stack.dir/flags.make
CMakeFiles/Stack.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Stack/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Stack.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Stack.dir/main.cpp.o -c /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Stack/main.cpp

CMakeFiles/Stack.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Stack.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Stack/main.cpp > CMakeFiles/Stack.dir/main.cpp.i

CMakeFiles/Stack.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Stack.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Stack/main.cpp -o CMakeFiles/Stack.dir/main.cpp.s

CMakeFiles/Stack.dir/LibStack.cpp.o: CMakeFiles/Stack.dir/flags.make
CMakeFiles/Stack.dir/LibStack.cpp.o: ../LibStack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Stack/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Stack.dir/LibStack.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Stack.dir/LibStack.cpp.o -c /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Stack/LibStack.cpp

CMakeFiles/Stack.dir/LibStack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Stack.dir/LibStack.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Stack/LibStack.cpp > CMakeFiles/Stack.dir/LibStack.cpp.i

CMakeFiles/Stack.dir/LibStack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Stack.dir/LibStack.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Stack/LibStack.cpp -o CMakeFiles/Stack.dir/LibStack.cpp.s

# Object files for target Stack
Stack_OBJECTS = \
"CMakeFiles/Stack.dir/main.cpp.o" \
"CMakeFiles/Stack.dir/LibStack.cpp.o"

# External object files for target Stack
Stack_EXTERNAL_OBJECTS =

Stack: CMakeFiles/Stack.dir/main.cpp.o
Stack: CMakeFiles/Stack.dir/LibStack.cpp.o
Stack: CMakeFiles/Stack.dir/build.make
Stack: CMakeFiles/Stack.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Stack/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Stack"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Stack.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Stack.dir/build: Stack
.PHONY : CMakeFiles/Stack.dir/build

CMakeFiles/Stack.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Stack.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Stack.dir/clean

CMakeFiles/Stack.dir/depend:
	cd /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Stack/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Stack /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Stack /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Stack/cmake-build-debug /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Stack/cmake-build-debug /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Stack/cmake-build-debug/CMakeFiles/Stack.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Stack.dir/depend

