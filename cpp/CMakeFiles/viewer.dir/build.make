# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\msys64\mingw64\bin\cmake.exe

# The command to remove a file.
RM = C:\msys64\mingw64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\nguye\Documents\GitHub\VirtualTour\cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\nguye\Documents\GitHub\VirtualTour\cpp

# Include any dependencies generated for this target.
include CMakeFiles/viewer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/viewer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/viewer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/viewer.dir/flags.make

CMakeFiles/viewer.dir/main.cpp.o: CMakeFiles/viewer.dir/flags.make
CMakeFiles/viewer.dir/main.cpp.o: main.cpp
CMakeFiles/viewer.dir/main.cpp.o: CMakeFiles/viewer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\nguye\Documents\GitHub\VirtualTour\cpp\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/viewer.dir/main.cpp.o"
	C:\Users\nguye\Downloads\emsdk-3.1.18\upstream\emscripten\em++.bat $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/viewer.dir/main.cpp.o -MF CMakeFiles\viewer.dir\main.cpp.o.d -o CMakeFiles\viewer.dir\main.cpp.o -c C:\Users\nguye\Documents\GitHub\VirtualTour\cpp\main.cpp

CMakeFiles/viewer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/viewer.dir/main.cpp.i"
	C:\Users\nguye\Downloads\emsdk-3.1.18\upstream\emscripten\em++.bat $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\nguye\Documents\GitHub\VirtualTour\cpp\main.cpp > CMakeFiles\viewer.dir\main.cpp.i

CMakeFiles/viewer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/viewer.dir/main.cpp.s"
	C:\Users\nguye\Downloads\emsdk-3.1.18\upstream\emscripten\em++.bat $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\nguye\Documents\GitHub\VirtualTour\cpp\main.cpp -o CMakeFiles\viewer.dir\main.cpp.s

# Object files for target viewer
viewer_OBJECTS = \
"CMakeFiles/viewer.dir/main.cpp.o"

# External object files for target viewer
viewer_EXTERNAL_OBJECTS =

viewer.js: CMakeFiles/viewer.dir/main.cpp.o
viewer.js: CMakeFiles/viewer.dir/build.make
viewer.js: CMakeFiles/viewer.dir/objects1.rsp
viewer.js: CMakeFiles/viewer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\nguye\Documents\GitHub\VirtualTour\cpp\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable viewer.js"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\viewer.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/viewer.dir/build: viewer.js
.PHONY : CMakeFiles/viewer.dir/build

CMakeFiles/viewer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\viewer.dir\cmake_clean.cmake
.PHONY : CMakeFiles/viewer.dir/clean

CMakeFiles/viewer.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\nguye\Documents\GitHub\VirtualTour\cpp C:\Users\nguye\Documents\GitHub\VirtualTour\cpp C:\Users\nguye\Documents\GitHub\VirtualTour\cpp C:\Users\nguye\Documents\GitHub\VirtualTour\cpp C:\Users\nguye\Documents\GitHub\VirtualTour\cpp\CMakeFiles\viewer.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/viewer.dir/depend

