# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_SOURCE_DIR = "/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main/build"

# Include any dependencies generated for this target.
include CMakeFiles/Ray.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Ray.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Ray.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Ray.dir/flags.make

CMakeFiles/Ray.dir/codegen:
.PHONY : CMakeFiles/Ray.dir/codegen

CMakeFiles/Ray.dir/src/Ray.cpp.o: CMakeFiles/Ray.dir/flags.make
CMakeFiles/Ray.dir/src/Ray.cpp.o: /home/gabechu/mdu/graphics/Ray\ Tracing\ Assignment/RayTracer-main/src/Ray.cpp
CMakeFiles/Ray.dir/src/Ray.cpp.o: CMakeFiles/Ray.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Ray.dir/src/Ray.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Ray.dir/src/Ray.cpp.o -MF CMakeFiles/Ray.dir/src/Ray.cpp.o.d -o CMakeFiles/Ray.dir/src/Ray.cpp.o -c "/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main/src/Ray.cpp"

CMakeFiles/Ray.dir/src/Ray.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Ray.dir/src/Ray.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main/src/Ray.cpp" > CMakeFiles/Ray.dir/src/Ray.cpp.i

CMakeFiles/Ray.dir/src/Ray.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Ray.dir/src/Ray.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main/src/Ray.cpp" -o CMakeFiles/Ray.dir/src/Ray.cpp.s

# Object files for target Ray
Ray_OBJECTS = \
"CMakeFiles/Ray.dir/src/Ray.cpp.o"

# External object files for target Ray
Ray_EXTERNAL_OBJECTS =

libRay.a: CMakeFiles/Ray.dir/src/Ray.cpp.o
libRay.a: CMakeFiles/Ray.dir/build.make
libRay.a: CMakeFiles/Ray.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libRay.a"
	$(CMAKE_COMMAND) -P CMakeFiles/Ray.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Ray.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Ray.dir/build: libRay.a
.PHONY : CMakeFiles/Ray.dir/build

CMakeFiles/Ray.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Ray.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Ray.dir/clean

CMakeFiles/Ray.dir/depend:
	cd "/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main" "/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main" "/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main/build" "/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main/build" "/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main/build/CMakeFiles/Ray.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/Ray.dir/depend

