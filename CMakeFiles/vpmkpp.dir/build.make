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
CMAKE_SOURCE_DIR = /home/aaaa0ggmc/Desktop/Projs/vpmkpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aaaa0ggmc/Desktop/Projs/vpmkpp

# Include any dependencies generated for this target.
include CMakeFiles/vpmkpp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/vpmkpp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/vpmkpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/vpmkpp.dir/flags.make

CMakeFiles/vpmkpp.dir/codegen:
.PHONY : CMakeFiles/vpmkpp.dir/codegen

CMakeFiles/vpmkpp.dir/src/main.cpp.o: CMakeFiles/vpmkpp.dir/flags.make
CMakeFiles/vpmkpp.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/vpmkpp.dir/src/main.cpp.o: CMakeFiles/vpmkpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/aaaa0ggmc/Desktop/Projs/vpmkpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/vpmkpp.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/vpmkpp.dir/src/main.cpp.o -MF CMakeFiles/vpmkpp.dir/src/main.cpp.o.d -o CMakeFiles/vpmkpp.dir/src/main.cpp.o -c /home/aaaa0ggmc/Desktop/Projs/vpmkpp/src/main.cpp

CMakeFiles/vpmkpp.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/vpmkpp.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aaaa0ggmc/Desktop/Projs/vpmkpp/src/main.cpp > CMakeFiles/vpmkpp.dir/src/main.cpp.i

CMakeFiles/vpmkpp.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/vpmkpp.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aaaa0ggmc/Desktop/Projs/vpmkpp/src/main.cpp -o CMakeFiles/vpmkpp.dir/src/main.cpp.s

# Object files for target vpmkpp
vpmkpp_OBJECTS = \
"CMakeFiles/vpmkpp.dir/src/main.cpp.o"

# External object files for target vpmkpp
vpmkpp_EXTERNAL_OBJECTS =

vpmkpp: CMakeFiles/vpmkpp.dir/src/main.cpp.o
vpmkpp: CMakeFiles/vpmkpp.dir/build.make
vpmkpp: CMakeFiles/vpmkpp.dir/compiler_depend.ts
vpmkpp: CMakeFiles/vpmkpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/aaaa0ggmc/Desktop/Projs/vpmkpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable vpmkpp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vpmkpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/vpmkpp.dir/build: vpmkpp
.PHONY : CMakeFiles/vpmkpp.dir/build

CMakeFiles/vpmkpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/vpmkpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/vpmkpp.dir/clean

CMakeFiles/vpmkpp.dir/depend:
	cd /home/aaaa0ggmc/Desktop/Projs/vpmkpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aaaa0ggmc/Desktop/Projs/vpmkpp /home/aaaa0ggmc/Desktop/Projs/vpmkpp /home/aaaa0ggmc/Desktop/Projs/vpmkpp /home/aaaa0ggmc/Desktop/Projs/vpmkpp /home/aaaa0ggmc/Desktop/Projs/vpmkpp/CMakeFiles/vpmkpp.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/vpmkpp.dir/depend

