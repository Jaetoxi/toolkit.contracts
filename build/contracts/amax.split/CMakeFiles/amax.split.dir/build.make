# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.24.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.24.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/richardchen/work/wasm.contracts/toolkit.contracts/contracts

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/richardchen/work/wasm.contracts/toolkit.contracts/build/contracts

# Include any dependencies generated for this target.
include amax.split/CMakeFiles/amax.split.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include amax.split/CMakeFiles/amax.split.dir/compiler_depend.make

# Include the progress variables for this target.
include amax.split/CMakeFiles/amax.split.dir/progress.make

# Include the compile flags for this target's objects.
include amax.split/CMakeFiles/amax.split.dir/flags.make

amax.split/CMakeFiles/amax.split.dir/src/tokensplit.cpp.obj: amax.split/CMakeFiles/amax.split.dir/flags.make
amax.split/CMakeFiles/amax.split.dir/src/tokensplit.cpp.obj: /Users/richardchen/work/wasm.contracts/toolkit.contracts/contracts/amax.split/src/tokensplit.cpp
amax.split/CMakeFiles/amax.split.dir/src/tokensplit.cpp.obj: amax.split/CMakeFiles/amax.split.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/richardchen/work/wasm.contracts/toolkit.contracts/build/contracts/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object amax.split/CMakeFiles/amax.split.dir/src/tokensplit.cpp.obj"
	cd /Users/richardchen/work/wasm.contracts/toolkit.contracts/build/contracts/amax.split && /usr/local/amax.cdt/bin/amax-cpp $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT amax.split/CMakeFiles/amax.split.dir/src/tokensplit.cpp.obj -MF CMakeFiles/amax.split.dir/src/tokensplit.cpp.obj.d -o CMakeFiles/amax.split.dir/src/tokensplit.cpp.obj -c /Users/richardchen/work/wasm.contracts/toolkit.contracts/contracts/amax.split/src/tokensplit.cpp

amax.split/CMakeFiles/amax.split.dir/src/tokensplit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/amax.split.dir/src/tokensplit.cpp.i"
	cd /Users/richardchen/work/wasm.contracts/toolkit.contracts/build/contracts/amax.split && /usr/local/amax.cdt/bin/amax-cpp $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/richardchen/work/wasm.contracts/toolkit.contracts/contracts/amax.split/src/tokensplit.cpp > CMakeFiles/amax.split.dir/src/tokensplit.cpp.i

amax.split/CMakeFiles/amax.split.dir/src/tokensplit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/amax.split.dir/src/tokensplit.cpp.s"
	cd /Users/richardchen/work/wasm.contracts/toolkit.contracts/build/contracts/amax.split && /usr/local/amax.cdt/bin/amax-cpp $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/richardchen/work/wasm.contracts/toolkit.contracts/contracts/amax.split/src/tokensplit.cpp -o CMakeFiles/amax.split.dir/src/tokensplit.cpp.s

# Object files for target amax.split
amax_split_OBJECTS = \
"CMakeFiles/amax.split.dir/src/tokensplit.cpp.obj"

# External object files for target amax.split
amax_split_EXTERNAL_OBJECTS =

amax.split/amax.split.wasm: amax.split/CMakeFiles/amax.split.dir/src/tokensplit.cpp.obj
amax.split/amax.split.wasm: amax.split/CMakeFiles/amax.split.dir/build.make
amax.split/amax.split.wasm: amax.split/CMakeFiles/amax.split.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/richardchen/work/wasm.contracts/toolkit.contracts/build/contracts/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable amax.split.wasm"
	cd /Users/richardchen/work/wasm.contracts/toolkit.contracts/build/contracts/amax.split && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/amax.split.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
amax.split/CMakeFiles/amax.split.dir/build: amax.split/amax.split.wasm
.PHONY : amax.split/CMakeFiles/amax.split.dir/build

amax.split/CMakeFiles/amax.split.dir/clean:
	cd /Users/richardchen/work/wasm.contracts/toolkit.contracts/build/contracts/amax.split && $(CMAKE_COMMAND) -P CMakeFiles/amax.split.dir/cmake_clean.cmake
.PHONY : amax.split/CMakeFiles/amax.split.dir/clean

amax.split/CMakeFiles/amax.split.dir/depend:
	cd /Users/richardchen/work/wasm.contracts/toolkit.contracts/build/contracts && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/richardchen/work/wasm.contracts/toolkit.contracts/contracts /Users/richardchen/work/wasm.contracts/toolkit.contracts/contracts/amax.split /Users/richardchen/work/wasm.contracts/toolkit.contracts/build/contracts /Users/richardchen/work/wasm.contracts/toolkit.contracts/build/contracts/amax.split /Users/richardchen/work/wasm.contracts/toolkit.contracts/build/contracts/amax.split/CMakeFiles/amax.split.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : amax.split/CMakeFiles/amax.split.dir/depend

