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
include xchain.owner/CMakeFiles/xchain.owner.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include xchain.owner/CMakeFiles/xchain.owner.dir/compiler_depend.make

# Include the progress variables for this target.
include xchain.owner/CMakeFiles/xchain.owner.dir/progress.make

# Include the compile flags for this target's objects.
include xchain.owner/CMakeFiles/xchain.owner.dir/flags.make

xchain.owner/CMakeFiles/xchain.owner.dir/src/xchain.owner.cpp.obj: xchain.owner/CMakeFiles/xchain.owner.dir/flags.make
xchain.owner/CMakeFiles/xchain.owner.dir/src/xchain.owner.cpp.obj: /Users/richardchen/work/wasm.contracts/toolkit.contracts/contracts/xchain.owner/src/xchain.owner.cpp
xchain.owner/CMakeFiles/xchain.owner.dir/src/xchain.owner.cpp.obj: xchain.owner/CMakeFiles/xchain.owner.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/richardchen/work/wasm.contracts/toolkit.contracts/build/contracts/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object xchain.owner/CMakeFiles/xchain.owner.dir/src/xchain.owner.cpp.obj"
	cd /Users/richardchen/work/wasm.contracts/toolkit.contracts/build/contracts/xchain.owner && /usr/local/amax.cdt/bin/amax-cpp $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT xchain.owner/CMakeFiles/xchain.owner.dir/src/xchain.owner.cpp.obj -MF CMakeFiles/xchain.owner.dir/src/xchain.owner.cpp.obj.d -o CMakeFiles/xchain.owner.dir/src/xchain.owner.cpp.obj -c /Users/richardchen/work/wasm.contracts/toolkit.contracts/contracts/xchain.owner/src/xchain.owner.cpp

xchain.owner/CMakeFiles/xchain.owner.dir/src/xchain.owner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xchain.owner.dir/src/xchain.owner.cpp.i"
	cd /Users/richardchen/work/wasm.contracts/toolkit.contracts/build/contracts/xchain.owner && /usr/local/amax.cdt/bin/amax-cpp $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/richardchen/work/wasm.contracts/toolkit.contracts/contracts/xchain.owner/src/xchain.owner.cpp > CMakeFiles/xchain.owner.dir/src/xchain.owner.cpp.i

xchain.owner/CMakeFiles/xchain.owner.dir/src/xchain.owner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xchain.owner.dir/src/xchain.owner.cpp.s"
	cd /Users/richardchen/work/wasm.contracts/toolkit.contracts/build/contracts/xchain.owner && /usr/local/amax.cdt/bin/amax-cpp $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/richardchen/work/wasm.contracts/toolkit.contracts/contracts/xchain.owner/src/xchain.owner.cpp -o CMakeFiles/xchain.owner.dir/src/xchain.owner.cpp.s

# Object files for target xchain.owner
xchain_owner_OBJECTS = \
"CMakeFiles/xchain.owner.dir/src/xchain.owner.cpp.obj"

# External object files for target xchain.owner
xchain_owner_EXTERNAL_OBJECTS =

xchain.owner/xchain.owner.wasm: xchain.owner/CMakeFiles/xchain.owner.dir/src/xchain.owner.cpp.obj
xchain.owner/xchain.owner.wasm: xchain.owner/CMakeFiles/xchain.owner.dir/build.make
xchain.owner/xchain.owner.wasm: xchain.owner/CMakeFiles/xchain.owner.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/richardchen/work/wasm.contracts/toolkit.contracts/build/contracts/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable xchain.owner.wasm"
	cd /Users/richardchen/work/wasm.contracts/toolkit.contracts/build/contracts/xchain.owner && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/xchain.owner.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
xchain.owner/CMakeFiles/xchain.owner.dir/build: xchain.owner/xchain.owner.wasm
.PHONY : xchain.owner/CMakeFiles/xchain.owner.dir/build

xchain.owner/CMakeFiles/xchain.owner.dir/clean:
	cd /Users/richardchen/work/wasm.contracts/toolkit.contracts/build/contracts/xchain.owner && $(CMAKE_COMMAND) -P CMakeFiles/xchain.owner.dir/cmake_clean.cmake
.PHONY : xchain.owner/CMakeFiles/xchain.owner.dir/clean

xchain.owner/CMakeFiles/xchain.owner.dir/depend:
	cd /Users/richardchen/work/wasm.contracts/toolkit.contracts/build/contracts && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/richardchen/work/wasm.contracts/toolkit.contracts/contracts /Users/richardchen/work/wasm.contracts/toolkit.contracts/contracts/xchain.owner /Users/richardchen/work/wasm.contracts/toolkit.contracts/build/contracts /Users/richardchen/work/wasm.contracts/toolkit.contracts/build/contracts/xchain.owner /Users/richardchen/work/wasm.contracts/toolkit.contracts/build/contracts/xchain.owner/CMakeFiles/xchain.owner.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : xchain.owner/CMakeFiles/xchain.owner.dir/depend

