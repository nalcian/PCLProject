# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alicannalci/Documents/PCLProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alicannalci/Documents/PCLProject/build

# Include any dependencies generated for this target.
include CMakeFiles/OGL_out.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/OGL_out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OGL_out.dir/flags.make

CMakeFiles/OGL_out.dir/src/oglTest.cpp.o: CMakeFiles/OGL_out.dir/flags.make
CMakeFiles/OGL_out.dir/src/oglTest.cpp.o: ../src/oglTest.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/alicannalci/Documents/PCLProject/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/OGL_out.dir/src/oglTest.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/OGL_out.dir/src/oglTest.cpp.o -c /Users/alicannalci/Documents/PCLProject/src/oglTest.cpp

CMakeFiles/OGL_out.dir/src/oglTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OGL_out.dir/src/oglTest.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/alicannalci/Documents/PCLProject/src/oglTest.cpp > CMakeFiles/OGL_out.dir/src/oglTest.cpp.i

CMakeFiles/OGL_out.dir/src/oglTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OGL_out.dir/src/oglTest.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/alicannalci/Documents/PCLProject/src/oglTest.cpp -o CMakeFiles/OGL_out.dir/src/oglTest.cpp.s

CMakeFiles/OGL_out.dir/src/oglTest.cpp.o.requires:
.PHONY : CMakeFiles/OGL_out.dir/src/oglTest.cpp.o.requires

CMakeFiles/OGL_out.dir/src/oglTest.cpp.o.provides: CMakeFiles/OGL_out.dir/src/oglTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/OGL_out.dir/build.make CMakeFiles/OGL_out.dir/src/oglTest.cpp.o.provides.build
.PHONY : CMakeFiles/OGL_out.dir/src/oglTest.cpp.o.provides

CMakeFiles/OGL_out.dir/src/oglTest.cpp.o.provides.build: CMakeFiles/OGL_out.dir/src/oglTest.cpp.o

# Object files for target OGL_out
OGL_out_OBJECTS = \
"CMakeFiles/OGL_out.dir/src/oglTest.cpp.o"

# External object files for target OGL_out
OGL_out_EXTERNAL_OBJECTS =

OGL_out: CMakeFiles/OGL_out.dir/src/oglTest.cpp.o
OGL_out: CMakeFiles/OGL_out.dir/build.make
OGL_out: CMakeFiles/OGL_out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable OGL_out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OGL_out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OGL_out.dir/build: OGL_out
.PHONY : CMakeFiles/OGL_out.dir/build

CMakeFiles/OGL_out.dir/requires: CMakeFiles/OGL_out.dir/src/oglTest.cpp.o.requires
.PHONY : CMakeFiles/OGL_out.dir/requires

CMakeFiles/OGL_out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OGL_out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OGL_out.dir/clean

CMakeFiles/OGL_out.dir/depend:
	cd /Users/alicannalci/Documents/PCLProject/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alicannalci/Documents/PCLProject /Users/alicannalci/Documents/PCLProject /Users/alicannalci/Documents/PCLProject/build /Users/alicannalci/Documents/PCLProject/build /Users/alicannalci/Documents/PCLProject/build/CMakeFiles/OGL_out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OGL_out.dir/depend

