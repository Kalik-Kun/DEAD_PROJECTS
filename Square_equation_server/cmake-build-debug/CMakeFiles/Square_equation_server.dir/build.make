# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /snap/clion/163/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/163/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Square_equation_server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Square_equation_server/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Square_equation_server.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Square_equation_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Square_equation_server.dir/flags.make

CMakeFiles/Square_equation_server.dir/main.cpp.o: CMakeFiles/Square_equation_server.dir/flags.make
CMakeFiles/Square_equation_server.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Square_equation_server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Square_equation_server.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Square_equation_server.dir/main.cpp.o -c /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Square_equation_server/main.cpp

CMakeFiles/Square_equation_server.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Square_equation_server.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Square_equation_server/main.cpp > CMakeFiles/Square_equation_server.dir/main.cpp.i

CMakeFiles/Square_equation_server.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Square_equation_server.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Square_equation_server/main.cpp -o CMakeFiles/Square_equation_server.dir/main.cpp.s

# Object files for target Square_equation_server
Square_equation_server_OBJECTS = \
"CMakeFiles/Square_equation_server.dir/main.cpp.o"

# External object files for target Square_equation_server
Square_equation_server_EXTERNAL_OBJECTS =

Square_equation_server: CMakeFiles/Square_equation_server.dir/main.cpp.o
Square_equation_server: CMakeFiles/Square_equation_server.dir/build.make
Square_equation_server: CMakeFiles/Square_equation_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Square_equation_server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Square_equation_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Square_equation_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Square_equation_server.dir/build: Square_equation_server
.PHONY : CMakeFiles/Square_equation_server.dir/build

CMakeFiles/Square_equation_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Square_equation_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Square_equation_server.dir/clean

CMakeFiles/Square_equation_server.dir/depend:
	cd /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Square_equation_server/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Square_equation_server /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Square_equation_server /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Square_equation_server/cmake-build-debug /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Square_equation_server/cmake-build-debug /home/arlik_null/Документы/GitHub/DEAD_PROJECTS/Square_equation_server/cmake-build-debug/CMakeFiles/Square_equation_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Square_equation_server.dir/depend

