# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sarebjay/code/projects/2d_platformer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sarebjay/code/projects/2d_platformer/build

# Include any dependencies generated for this target.
include CMakeFiles/2d_platformer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/2d_platformer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/2d_platformer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/2d_platformer.dir/flags.make

CMakeFiles/2d_platformer.dir/src/main.c.o: CMakeFiles/2d_platformer.dir/flags.make
CMakeFiles/2d_platformer.dir/src/main.c.o: ../src/main.c
CMakeFiles/2d_platformer.dir/src/main.c.o: CMakeFiles/2d_platformer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sarebjay/code/projects/2d_platformer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/2d_platformer.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/2d_platformer.dir/src/main.c.o -MF CMakeFiles/2d_platformer.dir/src/main.c.o.d -o CMakeFiles/2d_platformer.dir/src/main.c.o -c /home/sarebjay/code/projects/2d_platformer/src/main.c

CMakeFiles/2d_platformer.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/2d_platformer.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sarebjay/code/projects/2d_platformer/src/main.c > CMakeFiles/2d_platformer.dir/src/main.c.i

CMakeFiles/2d_platformer.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/2d_platformer.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sarebjay/code/projects/2d_platformer/src/main.c -o CMakeFiles/2d_platformer.dir/src/main.c.s

CMakeFiles/2d_platformer.dir/src/player.c.o: CMakeFiles/2d_platformer.dir/flags.make
CMakeFiles/2d_platformer.dir/src/player.c.o: ../src/player.c
CMakeFiles/2d_platformer.dir/src/player.c.o: CMakeFiles/2d_platformer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sarebjay/code/projects/2d_platformer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/2d_platformer.dir/src/player.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/2d_platformer.dir/src/player.c.o -MF CMakeFiles/2d_platformer.dir/src/player.c.o.d -o CMakeFiles/2d_platformer.dir/src/player.c.o -c /home/sarebjay/code/projects/2d_platformer/src/player.c

CMakeFiles/2d_platformer.dir/src/player.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/2d_platformer.dir/src/player.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sarebjay/code/projects/2d_platformer/src/player.c > CMakeFiles/2d_platformer.dir/src/player.c.i

CMakeFiles/2d_platformer.dir/src/player.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/2d_platformer.dir/src/player.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sarebjay/code/projects/2d_platformer/src/player.c -o CMakeFiles/2d_platformer.dir/src/player.c.s

CMakeFiles/2d_platformer.dir/src/tile.c.o: CMakeFiles/2d_platformer.dir/flags.make
CMakeFiles/2d_platformer.dir/src/tile.c.o: ../src/tile.c
CMakeFiles/2d_platformer.dir/src/tile.c.o: CMakeFiles/2d_platformer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sarebjay/code/projects/2d_platformer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/2d_platformer.dir/src/tile.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/2d_platformer.dir/src/tile.c.o -MF CMakeFiles/2d_platformer.dir/src/tile.c.o.d -o CMakeFiles/2d_platformer.dir/src/tile.c.o -c /home/sarebjay/code/projects/2d_platformer/src/tile.c

CMakeFiles/2d_platformer.dir/src/tile.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/2d_platformer.dir/src/tile.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sarebjay/code/projects/2d_platformer/src/tile.c > CMakeFiles/2d_platformer.dir/src/tile.c.i

CMakeFiles/2d_platformer.dir/src/tile.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/2d_platformer.dir/src/tile.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sarebjay/code/projects/2d_platformer/src/tile.c -o CMakeFiles/2d_platformer.dir/src/tile.c.s

# Object files for target 2d_platformer
2d_platformer_OBJECTS = \
"CMakeFiles/2d_platformer.dir/src/main.c.o" \
"CMakeFiles/2d_platformer.dir/src/player.c.o" \
"CMakeFiles/2d_platformer.dir/src/tile.c.o"

# External object files for target 2d_platformer
2d_platformer_EXTERNAL_OBJECTS =

2d_platformer: CMakeFiles/2d_platformer.dir/src/main.c.o
2d_platformer: CMakeFiles/2d_platformer.dir/src/player.c.o
2d_platformer: CMakeFiles/2d_platformer.dir/src/tile.c.o
2d_platformer: CMakeFiles/2d_platformer.dir/build.make
2d_platformer: CMakeFiles/2d_platformer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sarebjay/code/projects/2d_platformer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable 2d_platformer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/2d_platformer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/2d_platformer.dir/build: 2d_platformer
.PHONY : CMakeFiles/2d_platformer.dir/build

CMakeFiles/2d_platformer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/2d_platformer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/2d_platformer.dir/clean

CMakeFiles/2d_platformer.dir/depend:
	cd /home/sarebjay/code/projects/2d_platformer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sarebjay/code/projects/2d_platformer /home/sarebjay/code/projects/2d_platformer /home/sarebjay/code/projects/2d_platformer/build /home/sarebjay/code/projects/2d_platformer/build /home/sarebjay/code/projects/2d_platformer/build/CMakeFiles/2d_platformer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/2d_platformer.dir/depend

