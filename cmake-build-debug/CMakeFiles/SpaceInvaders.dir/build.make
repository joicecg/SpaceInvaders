# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/I863256/Documents/Unisinos/pg/SpaceInvaders

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/I863256/Documents/Unisinos/pg/SpaceInvaders/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SpaceInvaders.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SpaceInvaders.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SpaceInvaders.dir/flags.make

CMakeFiles/SpaceInvaders.dir/envaders/main.cpp.o: CMakeFiles/SpaceInvaders.dir/flags.make
CMakeFiles/SpaceInvaders.dir/envaders/main.cpp.o: ../envaders/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/I863256/Documents/Unisinos/pg/SpaceInvaders/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SpaceInvaders.dir/envaders/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SpaceInvaders.dir/envaders/main.cpp.o -c /home/I863256/Documents/Unisinos/pg/SpaceInvaders/envaders/main.cpp

CMakeFiles/SpaceInvaders.dir/envaders/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SpaceInvaders.dir/envaders/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/I863256/Documents/Unisinos/pg/SpaceInvaders/envaders/main.cpp > CMakeFiles/SpaceInvaders.dir/envaders/main.cpp.i

CMakeFiles/SpaceInvaders.dir/envaders/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SpaceInvaders.dir/envaders/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/I863256/Documents/Unisinos/pg/SpaceInvaders/envaders/main.cpp -o CMakeFiles/SpaceInvaders.dir/envaders/main.cpp.s

CMakeFiles/SpaceInvaders.dir/envaders/gl_utils.cpp.o: CMakeFiles/SpaceInvaders.dir/flags.make
CMakeFiles/SpaceInvaders.dir/envaders/gl_utils.cpp.o: ../envaders/gl_utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/I863256/Documents/Unisinos/pg/SpaceInvaders/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SpaceInvaders.dir/envaders/gl_utils.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SpaceInvaders.dir/envaders/gl_utils.cpp.o -c /home/I863256/Documents/Unisinos/pg/SpaceInvaders/envaders/gl_utils.cpp

CMakeFiles/SpaceInvaders.dir/envaders/gl_utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SpaceInvaders.dir/envaders/gl_utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/I863256/Documents/Unisinos/pg/SpaceInvaders/envaders/gl_utils.cpp > CMakeFiles/SpaceInvaders.dir/envaders/gl_utils.cpp.i

CMakeFiles/SpaceInvaders.dir/envaders/gl_utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SpaceInvaders.dir/envaders/gl_utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/I863256/Documents/Unisinos/pg/SpaceInvaders/envaders/gl_utils.cpp -o CMakeFiles/SpaceInvaders.dir/envaders/gl_utils.cpp.s

CMakeFiles/SpaceInvaders.dir/envaders/maths_funcs.cpp.o: CMakeFiles/SpaceInvaders.dir/flags.make
CMakeFiles/SpaceInvaders.dir/envaders/maths_funcs.cpp.o: ../envaders/maths_funcs.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/I863256/Documents/Unisinos/pg/SpaceInvaders/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/SpaceInvaders.dir/envaders/maths_funcs.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SpaceInvaders.dir/envaders/maths_funcs.cpp.o -c /home/I863256/Documents/Unisinos/pg/SpaceInvaders/envaders/maths_funcs.cpp

CMakeFiles/SpaceInvaders.dir/envaders/maths_funcs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SpaceInvaders.dir/envaders/maths_funcs.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/I863256/Documents/Unisinos/pg/SpaceInvaders/envaders/maths_funcs.cpp > CMakeFiles/SpaceInvaders.dir/envaders/maths_funcs.cpp.i

CMakeFiles/SpaceInvaders.dir/envaders/maths_funcs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SpaceInvaders.dir/envaders/maths_funcs.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/I863256/Documents/Unisinos/pg/SpaceInvaders/envaders/maths_funcs.cpp -o CMakeFiles/SpaceInvaders.dir/envaders/maths_funcs.cpp.s

# Object files for target SpaceInvaders
SpaceInvaders_OBJECTS = \
"CMakeFiles/SpaceInvaders.dir/envaders/main.cpp.o" \
"CMakeFiles/SpaceInvaders.dir/envaders/gl_utils.cpp.o" \
"CMakeFiles/SpaceInvaders.dir/envaders/maths_funcs.cpp.o"

# External object files for target SpaceInvaders
SpaceInvaders_EXTERNAL_OBJECTS =

SpaceInvaders: CMakeFiles/SpaceInvaders.dir/envaders/main.cpp.o
SpaceInvaders: CMakeFiles/SpaceInvaders.dir/envaders/gl_utils.cpp.o
SpaceInvaders: CMakeFiles/SpaceInvaders.dir/envaders/maths_funcs.cpp.o
SpaceInvaders: CMakeFiles/SpaceInvaders.dir/build.make
SpaceInvaders: /usr/lib/x86_64-linux-gnu/libGLEW.so
SpaceInvaders: /usr/lib/x86_64-linux-gnu/libGL.so
SpaceInvaders: /usr/lib/x86_64-linux-gnu/libGLU.so
SpaceInvaders: /usr/lib/x86_64-linux-gnu/libglut.so
SpaceInvaders: /usr/lib/x86_64-linux-gnu/libXmu.so
SpaceInvaders: /usr/lib/x86_64-linux-gnu/libXi.so
SpaceInvaders: /usr/lib/x86_64-linux-gnu/libGLEW.so
SpaceInvaders: /usr/lib/x86_64-linux-gnu/libGL.so
SpaceInvaders: /usr/lib/x86_64-linux-gnu/libGLU.so
SpaceInvaders: /usr/lib/x86_64-linux-gnu/libglut.so
SpaceInvaders: /usr/lib/x86_64-linux-gnu/libXmu.so
SpaceInvaders: /usr/lib/x86_64-linux-gnu/libXi.so
SpaceInvaders: CMakeFiles/SpaceInvaders.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/I863256/Documents/Unisinos/pg/SpaceInvaders/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable SpaceInvaders"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SpaceInvaders.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SpaceInvaders.dir/build: SpaceInvaders

.PHONY : CMakeFiles/SpaceInvaders.dir/build

CMakeFiles/SpaceInvaders.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SpaceInvaders.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SpaceInvaders.dir/clean

CMakeFiles/SpaceInvaders.dir/depend:
	cd /home/I863256/Documents/Unisinos/pg/SpaceInvaders/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/I863256/Documents/Unisinos/pg/SpaceInvaders /home/I863256/Documents/Unisinos/pg/SpaceInvaders /home/I863256/Documents/Unisinos/pg/SpaceInvaders/cmake-build-debug /home/I863256/Documents/Unisinos/pg/SpaceInvaders/cmake-build-debug /home/I863256/Documents/Unisinos/pg/SpaceInvaders/cmake-build-debug/CMakeFiles/SpaceInvaders.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SpaceInvaders.dir/depend

