# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/rjzhb/Project/slimpajama-cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rjzhb/Project/slimpajama-cpp/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/slimpajama.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/slimpajama.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/slimpajama.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/slimpajama.dir/flags.make

CMakeFiles/slimpajama.dir/benchmark.cpp.o: CMakeFiles/slimpajama.dir/flags.make
CMakeFiles/slimpajama.dir/benchmark.cpp.o: ../benchmark.cpp
CMakeFiles/slimpajama.dir/benchmark.cpp.o: CMakeFiles/slimpajama.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rjzhb/Project/slimpajama-cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/slimpajama.dir/benchmark.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/slimpajama.dir/benchmark.cpp.o -MF CMakeFiles/slimpajama.dir/benchmark.cpp.o.d -o CMakeFiles/slimpajama.dir/benchmark.cpp.o -c /home/rjzhb/Project/slimpajama-cpp/benchmark.cpp

CMakeFiles/slimpajama.dir/benchmark.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/slimpajama.dir/benchmark.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rjzhb/Project/slimpajama-cpp/benchmark.cpp > CMakeFiles/slimpajama.dir/benchmark.cpp.i

CMakeFiles/slimpajama.dir/benchmark.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/slimpajama.dir/benchmark.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rjzhb/Project/slimpajama-cpp/benchmark.cpp -o CMakeFiles/slimpajama.dir/benchmark.cpp.s

CMakeFiles/slimpajama.dir/src/preprocessing/normalize_text.cpp.o: CMakeFiles/slimpajama.dir/flags.make
CMakeFiles/slimpajama.dir/src/preprocessing/normalize_text.cpp.o: ../src/preprocessing/normalize_text.cpp
CMakeFiles/slimpajama.dir/src/preprocessing/normalize_text.cpp.o: CMakeFiles/slimpajama.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rjzhb/Project/slimpajama-cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/slimpajama.dir/src/preprocessing/normalize_text.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/slimpajama.dir/src/preprocessing/normalize_text.cpp.o -MF CMakeFiles/slimpajama.dir/src/preprocessing/normalize_text.cpp.o.d -o CMakeFiles/slimpajama.dir/src/preprocessing/normalize_text.cpp.o -c /home/rjzhb/Project/slimpajama-cpp/src/preprocessing/normalize_text.cpp

CMakeFiles/slimpajama.dir/src/preprocessing/normalize_text.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/slimpajama.dir/src/preprocessing/normalize_text.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rjzhb/Project/slimpajama-cpp/src/preprocessing/normalize_text.cpp > CMakeFiles/slimpajama.dir/src/preprocessing/normalize_text.cpp.i

CMakeFiles/slimpajama.dir/src/preprocessing/normalize_text.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/slimpajama.dir/src/preprocessing/normalize_text.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rjzhb/Project/slimpajama-cpp/src/preprocessing/normalize_text.cpp -o CMakeFiles/slimpajama.dir/src/preprocessing/normalize_text.cpp.s

CMakeFiles/slimpajama.dir/src/preprocessing/filter.cpp.o: CMakeFiles/slimpajama.dir/flags.make
CMakeFiles/slimpajama.dir/src/preprocessing/filter.cpp.o: ../src/preprocessing/filter.cpp
CMakeFiles/slimpajama.dir/src/preprocessing/filter.cpp.o: CMakeFiles/slimpajama.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rjzhb/Project/slimpajama-cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/slimpajama.dir/src/preprocessing/filter.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/slimpajama.dir/src/preprocessing/filter.cpp.o -MF CMakeFiles/slimpajama.dir/src/preprocessing/filter.cpp.o.d -o CMakeFiles/slimpajama.dir/src/preprocessing/filter.cpp.o -c /home/rjzhb/Project/slimpajama-cpp/src/preprocessing/filter.cpp

CMakeFiles/slimpajama.dir/src/preprocessing/filter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/slimpajama.dir/src/preprocessing/filter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rjzhb/Project/slimpajama-cpp/src/preprocessing/filter.cpp > CMakeFiles/slimpajama.dir/src/preprocessing/filter.cpp.i

CMakeFiles/slimpajama.dir/src/preprocessing/filter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/slimpajama.dir/src/preprocessing/filter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rjzhb/Project/slimpajama-cpp/src/preprocessing/filter.cpp -o CMakeFiles/slimpajama.dir/src/preprocessing/filter.cpp.s

CMakeFiles/slimpajama.dir/src/preprocessing/ToHash.cpp.o: CMakeFiles/slimpajama.dir/flags.make
CMakeFiles/slimpajama.dir/src/preprocessing/ToHash.cpp.o: ../src/preprocessing/ToHash.cpp
CMakeFiles/slimpajama.dir/src/preprocessing/ToHash.cpp.o: CMakeFiles/slimpajama.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rjzhb/Project/slimpajama-cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/slimpajama.dir/src/preprocessing/ToHash.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/slimpajama.dir/src/preprocessing/ToHash.cpp.o -MF CMakeFiles/slimpajama.dir/src/preprocessing/ToHash.cpp.o.d -o CMakeFiles/slimpajama.dir/src/preprocessing/ToHash.cpp.o -c /home/rjzhb/Project/slimpajama-cpp/src/preprocessing/ToHash.cpp

CMakeFiles/slimpajama.dir/src/preprocessing/ToHash.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/slimpajama.dir/src/preprocessing/ToHash.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rjzhb/Project/slimpajama-cpp/src/preprocessing/ToHash.cpp > CMakeFiles/slimpajama.dir/src/preprocessing/ToHash.cpp.i

CMakeFiles/slimpajama.dir/src/preprocessing/ToHash.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/slimpajama.dir/src/preprocessing/ToHash.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rjzhb/Project/slimpajama-cpp/src/preprocessing/ToHash.cpp -o CMakeFiles/slimpajama.dir/src/preprocessing/ToHash.cpp.s

CMakeFiles/slimpajama.dir/src/dedup/DuplicatePairs.cpp.o: CMakeFiles/slimpajama.dir/flags.make
CMakeFiles/slimpajama.dir/src/dedup/DuplicatePairs.cpp.o: ../src/dedup/DuplicatePairs.cpp
CMakeFiles/slimpajama.dir/src/dedup/DuplicatePairs.cpp.o: CMakeFiles/slimpajama.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rjzhb/Project/slimpajama-cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/slimpajama.dir/src/dedup/DuplicatePairs.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/slimpajama.dir/src/dedup/DuplicatePairs.cpp.o -MF CMakeFiles/slimpajama.dir/src/dedup/DuplicatePairs.cpp.o.d -o CMakeFiles/slimpajama.dir/src/dedup/DuplicatePairs.cpp.o -c /home/rjzhb/Project/slimpajama-cpp/src/dedup/DuplicatePairs.cpp

CMakeFiles/slimpajama.dir/src/dedup/DuplicatePairs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/slimpajama.dir/src/dedup/DuplicatePairs.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rjzhb/Project/slimpajama-cpp/src/dedup/DuplicatePairs.cpp > CMakeFiles/slimpajama.dir/src/dedup/DuplicatePairs.cpp.i

CMakeFiles/slimpajama.dir/src/dedup/DuplicatePairs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/slimpajama.dir/src/dedup/DuplicatePairs.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rjzhb/Project/slimpajama-cpp/src/dedup/DuplicatePairs.cpp -o CMakeFiles/slimpajama.dir/src/dedup/DuplicatePairs.cpp.s

CMakeFiles/slimpajama.dir/src/utils/Utils.cpp.o: CMakeFiles/slimpajama.dir/flags.make
CMakeFiles/slimpajama.dir/src/utils/Utils.cpp.o: ../src/utils/Utils.cpp
CMakeFiles/slimpajama.dir/src/utils/Utils.cpp.o: CMakeFiles/slimpajama.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rjzhb/Project/slimpajama-cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/slimpajama.dir/src/utils/Utils.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/slimpajama.dir/src/utils/Utils.cpp.o -MF CMakeFiles/slimpajama.dir/src/utils/Utils.cpp.o.d -o CMakeFiles/slimpajama.dir/src/utils/Utils.cpp.o -c /home/rjzhb/Project/slimpajama-cpp/src/utils/Utils.cpp

CMakeFiles/slimpajama.dir/src/utils/Utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/slimpajama.dir/src/utils/Utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rjzhb/Project/slimpajama-cpp/src/utils/Utils.cpp > CMakeFiles/slimpajama.dir/src/utils/Utils.cpp.i

CMakeFiles/slimpajama.dir/src/utils/Utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/slimpajama.dir/src/utils/Utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rjzhb/Project/slimpajama-cpp/src/utils/Utils.cpp -o CMakeFiles/slimpajama.dir/src/utils/Utils.cpp.s

# Object files for target slimpajama
slimpajama_OBJECTS = \
"CMakeFiles/slimpajama.dir/benchmark.cpp.o" \
"CMakeFiles/slimpajama.dir/src/preprocessing/normalize_text.cpp.o" \
"CMakeFiles/slimpajama.dir/src/preprocessing/filter.cpp.o" \
"CMakeFiles/slimpajama.dir/src/preprocessing/ToHash.cpp.o" \
"CMakeFiles/slimpajama.dir/src/dedup/DuplicatePairs.cpp.o" \
"CMakeFiles/slimpajama.dir/src/utils/Utils.cpp.o"

# External object files for target slimpajama
slimpajama_EXTERNAL_OBJECTS =

slimpajama: CMakeFiles/slimpajama.dir/benchmark.cpp.o
slimpajama: CMakeFiles/slimpajama.dir/src/preprocessing/normalize_text.cpp.o
slimpajama: CMakeFiles/slimpajama.dir/src/preprocessing/filter.cpp.o
slimpajama: CMakeFiles/slimpajama.dir/src/preprocessing/ToHash.cpp.o
slimpajama: CMakeFiles/slimpajama.dir/src/dedup/DuplicatePairs.cpp.o
slimpajama: CMakeFiles/slimpajama.dir/src/utils/Utils.cpp.o
slimpajama: CMakeFiles/slimpajama.dir/build.make
slimpajama: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.74.0
slimpajama: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.74.0
slimpajama: /usr/lib/x86_64-linux-gnu/libboost_serialization.so.1.74.0
slimpajama: CMakeFiles/slimpajama.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rjzhb/Project/slimpajama-cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable slimpajama"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/slimpajama.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/slimpajama.dir/build: slimpajama
.PHONY : CMakeFiles/slimpajama.dir/build

CMakeFiles/slimpajama.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/slimpajama.dir/cmake_clean.cmake
.PHONY : CMakeFiles/slimpajama.dir/clean

CMakeFiles/slimpajama.dir/depend:
	cd /home/rjzhb/Project/slimpajama-cpp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rjzhb/Project/slimpajama-cpp /home/rjzhb/Project/slimpajama-cpp /home/rjzhb/Project/slimpajama-cpp/cmake-build-debug /home/rjzhb/Project/slimpajama-cpp/cmake-build-debug /home/rjzhb/Project/slimpajama-cpp/cmake-build-debug/CMakeFiles/slimpajama.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/slimpajama.dir/depend

