# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /app/socket套接字

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /app/socket套接字/build

# Include any dependencies generated for this target.
include CMakeFiles/simple_client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/simple_client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/simple_client.dir/flags.make

CMakeFiles/simple_client.dir/simple/simple_client.cpp.o: CMakeFiles/simple_client.dir/flags.make
CMakeFiles/simple_client.dir/simple/simple_client.cpp.o: ../simple/simple_client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/app/socket套接字/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/simple_client.dir/simple/simple_client.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/simple_client.dir/simple/simple_client.cpp.o -c /app/socket套接字/simple/simple_client.cpp

CMakeFiles/simple_client.dir/simple/simple_client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simple_client.dir/simple/simple_client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /app/socket套接字/simple/simple_client.cpp > CMakeFiles/simple_client.dir/simple/simple_client.cpp.i

CMakeFiles/simple_client.dir/simple/simple_client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simple_client.dir/simple/simple_client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /app/socket套接字/simple/simple_client.cpp -o CMakeFiles/simple_client.dir/simple/simple_client.cpp.s

# Object files for target simple_client
simple_client_OBJECTS = \
"CMakeFiles/simple_client.dir/simple/simple_client.cpp.o"

# External object files for target simple_client
simple_client_EXTERNAL_OBJECTS =

simple_client: CMakeFiles/simple_client.dir/simple/simple_client.cpp.o
simple_client: CMakeFiles/simple_client.dir/build.make
simple_client: CMakeFiles/simple_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/app/socket套接字/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable simple_client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simple_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/simple_client.dir/build: simple_client

.PHONY : CMakeFiles/simple_client.dir/build

CMakeFiles/simple_client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/simple_client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/simple_client.dir/clean

CMakeFiles/simple_client.dir/depend:
	cd /app/socket套接字/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /app/socket套接字 /app/socket套接字 /app/socket套接字/build /app/socket套接字/build /app/socket套接字/build/CMakeFiles/simple_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/simple_client.dir/depend

