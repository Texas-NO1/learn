# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /app/learn/grpc-memory

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /app/learn/grpc-memory/build

# Include any dependencies generated for this target.
include CMakeFiles/client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client.dir/flags.make

CMakeFiles/client.dir/src/grpc_client.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/src/grpc_client.cpp.o: ../src/grpc_client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/app/learn/grpc-memory/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/client.dir/src/grpc_client.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/src/grpc_client.cpp.o -c /app/learn/grpc-memory/src/grpc_client.cpp

CMakeFiles/client.dir/src/grpc_client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/src/grpc_client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /app/learn/grpc-memory/src/grpc_client.cpp > CMakeFiles/client.dir/src/grpc_client.cpp.i

CMakeFiles/client.dir/src/grpc_client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/src/grpc_client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /app/learn/grpc-memory/src/grpc_client.cpp -o CMakeFiles/client.dir/src/grpc_client.cpp.s

CMakeFiles/client.dir/src/generated/template.grpc.pb.cc.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/src/generated/template.grpc.pb.cc.o: ../src/generated/template.grpc.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/app/learn/grpc-memory/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/client.dir/src/generated/template.grpc.pb.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/src/generated/template.grpc.pb.cc.o -c /app/learn/grpc-memory/src/generated/template.grpc.pb.cc

CMakeFiles/client.dir/src/generated/template.grpc.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/src/generated/template.grpc.pb.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /app/learn/grpc-memory/src/generated/template.grpc.pb.cc > CMakeFiles/client.dir/src/generated/template.grpc.pb.cc.i

CMakeFiles/client.dir/src/generated/template.grpc.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/src/generated/template.grpc.pb.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /app/learn/grpc-memory/src/generated/template.grpc.pb.cc -o CMakeFiles/client.dir/src/generated/template.grpc.pb.cc.s

CMakeFiles/client.dir/src/generated/template.pb.cc.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/src/generated/template.pb.cc.o: ../src/generated/template.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/app/learn/grpc-memory/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/client.dir/src/generated/template.pb.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/src/generated/template.pb.cc.o -c /app/learn/grpc-memory/src/generated/template.pb.cc

CMakeFiles/client.dir/src/generated/template.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/src/generated/template.pb.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /app/learn/grpc-memory/src/generated/template.pb.cc > CMakeFiles/client.dir/src/generated/template.pb.cc.i

CMakeFiles/client.dir/src/generated/template.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/src/generated/template.pb.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /app/learn/grpc-memory/src/generated/template.pb.cc -o CMakeFiles/client.dir/src/generated/template.pb.cc.s

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/src/grpc_client.cpp.o" \
"CMakeFiles/client.dir/src/generated/template.grpc.pb.cc.o" \
"CMakeFiles/client.dir/src/generated/template.pb.cc.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

client: CMakeFiles/client.dir/src/grpc_client.cpp.o
client: CMakeFiles/client.dir/src/generated/template.grpc.pb.cc.o
client: CMakeFiles/client.dir/src/generated/template.pb.cc.o
client: CMakeFiles/client.dir/build.make
client: /usr/local/lib/libjemalloc.so
client: CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/app/learn/grpc-memory/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client.dir/build: client

.PHONY : CMakeFiles/client.dir/build

CMakeFiles/client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client.dir/clean

CMakeFiles/client.dir/depend:
	cd /app/learn/grpc-memory/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /app/learn/grpc-memory /app/learn/grpc-memory /app/learn/grpc-memory/build /app/learn/grpc-memory/build /app/learn/grpc-memory/build/CMakeFiles/client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/client.dir/depend

