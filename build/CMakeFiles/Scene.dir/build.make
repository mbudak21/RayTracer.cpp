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
include CMakeFiles/Scene.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Scene.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Scene.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Scene.dir/flags.make

CMakeFiles/Scene.dir/codegen:
.PHONY : CMakeFiles/Scene.dir/codegen

CMakeFiles/Scene.dir/src/Scene.cpp.o: CMakeFiles/Scene.dir/flags.make
CMakeFiles/Scene.dir/src/Scene.cpp.o: /home/gabechu/mdu/graphics/Ray\ Tracing\ Assignment/RayTracer-main/src/Scene.cpp
CMakeFiles/Scene.dir/src/Scene.cpp.o: CMakeFiles/Scene.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Scene.dir/src/Scene.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Scene.dir/src/Scene.cpp.o -MF CMakeFiles/Scene.dir/src/Scene.cpp.o.d -o CMakeFiles/Scene.dir/src/Scene.cpp.o -c "/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main/src/Scene.cpp"

CMakeFiles/Scene.dir/src/Scene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Scene.dir/src/Scene.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main/src/Scene.cpp" > CMakeFiles/Scene.dir/src/Scene.cpp.i

CMakeFiles/Scene.dir/src/Scene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Scene.dir/src/Scene.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main/src/Scene.cpp" -o CMakeFiles/Scene.dir/src/Scene.cpp.s

# Object files for target Scene
Scene_OBJECTS = \
"CMakeFiles/Scene.dir/src/Scene.cpp.o"

# External object files for target Scene
Scene_EXTERNAL_OBJECTS =

libScene.a: CMakeFiles/Scene.dir/src/Scene.cpp.o
libScene.a: CMakeFiles/Scene.dir/build.make
libScene.a: CMakeFiles/Scene.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libScene.a"
	$(CMAKE_COMMAND) -P CMakeFiles/Scene.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Scene.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Scene.dir/build: libScene.a
.PHONY : CMakeFiles/Scene.dir/build

CMakeFiles/Scene.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Scene.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Scene.dir/clean

CMakeFiles/Scene.dir/depend:
	cd "/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main" "/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main" "/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main/build" "/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main/build" "/home/gabechu/mdu/graphics/Ray Tracing Assignment/RayTracer-main/build/CMakeFiles/Scene.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/Scene.dir/depend

