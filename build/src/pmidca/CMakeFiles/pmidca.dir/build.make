# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/local/lib/python2.7/dist-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /usr/local/lib/python2.7/dist-packages/cmake/data/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sampath/moos-ivp/moos-ivp-midca

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sampath/moos-ivp/moos-ivp-midca/build

# Include any dependencies generated for this target.
include src/pmidca/CMakeFiles/pmidca.dir/depend.make

# Include the progress variables for this target.
include src/pmidca/CMakeFiles/pmidca.dir/progress.make

# Include the compile flags for this target's objects.
include src/pmidca/CMakeFiles/pmidca.dir/flags.make

src/pmidca/CMakeFiles/pmidca.dir/midca.cpp.o: src/pmidca/CMakeFiles/pmidca.dir/flags.make
src/pmidca/CMakeFiles/pmidca.dir/midca.cpp.o: ../src/pmidca/midca.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sampath/moos-ivp/moos-ivp-midca/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/pmidca/CMakeFiles/pmidca.dir/midca.cpp.o"
	cd /home/sampath/moos-ivp/moos-ivp-midca/build/src/pmidca && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pmidca.dir/midca.cpp.o -c /home/sampath/moos-ivp/moos-ivp-midca/src/pmidca/midca.cpp

src/pmidca/CMakeFiles/pmidca.dir/midca.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pmidca.dir/midca.cpp.i"
	cd /home/sampath/moos-ivp/moos-ivp-midca/build/src/pmidca && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sampath/moos-ivp/moos-ivp-midca/src/pmidca/midca.cpp > CMakeFiles/pmidca.dir/midca.cpp.i

src/pmidca/CMakeFiles/pmidca.dir/midca.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pmidca.dir/midca.cpp.s"
	cd /home/sampath/moos-ivp/moos-ivp-midca/build/src/pmidca && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sampath/moos-ivp/moos-ivp-midca/src/pmidca/midca.cpp -o CMakeFiles/pmidca.dir/midca.cpp.s

src/pmidca/CMakeFiles/pmidca.dir/midca.cpp.o.requires:

.PHONY : src/pmidca/CMakeFiles/pmidca.dir/midca.cpp.o.requires

src/pmidca/CMakeFiles/pmidca.dir/midca.cpp.o.provides: src/pmidca/CMakeFiles/pmidca.dir/midca.cpp.o.requires
	$(MAKE) -f src/pmidca/CMakeFiles/pmidca.dir/build.make src/pmidca/CMakeFiles/pmidca.dir/midca.cpp.o.provides.build
.PHONY : src/pmidca/CMakeFiles/pmidca.dir/midca.cpp.o.provides

src/pmidca/CMakeFiles/pmidca.dir/midca.cpp.o.provides.build: src/pmidca/CMakeFiles/pmidca.dir/midca.cpp.o


src/pmidca/CMakeFiles/pmidca.dir/midca_Info.cpp.o: src/pmidca/CMakeFiles/pmidca.dir/flags.make
src/pmidca/CMakeFiles/pmidca.dir/midca_Info.cpp.o: ../src/pmidca/midca_Info.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sampath/moos-ivp/moos-ivp-midca/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/pmidca/CMakeFiles/pmidca.dir/midca_Info.cpp.o"
	cd /home/sampath/moos-ivp/moos-ivp-midca/build/src/pmidca && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pmidca.dir/midca_Info.cpp.o -c /home/sampath/moos-ivp/moos-ivp-midca/src/pmidca/midca_Info.cpp

src/pmidca/CMakeFiles/pmidca.dir/midca_Info.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pmidca.dir/midca_Info.cpp.i"
	cd /home/sampath/moos-ivp/moos-ivp-midca/build/src/pmidca && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sampath/moos-ivp/moos-ivp-midca/src/pmidca/midca_Info.cpp > CMakeFiles/pmidca.dir/midca_Info.cpp.i

src/pmidca/CMakeFiles/pmidca.dir/midca_Info.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pmidca.dir/midca_Info.cpp.s"
	cd /home/sampath/moos-ivp/moos-ivp-midca/build/src/pmidca && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sampath/moos-ivp/moos-ivp-midca/src/pmidca/midca_Info.cpp -o CMakeFiles/pmidca.dir/midca_Info.cpp.s

src/pmidca/CMakeFiles/pmidca.dir/midca_Info.cpp.o.requires:

.PHONY : src/pmidca/CMakeFiles/pmidca.dir/midca_Info.cpp.o.requires

src/pmidca/CMakeFiles/pmidca.dir/midca_Info.cpp.o.provides: src/pmidca/CMakeFiles/pmidca.dir/midca_Info.cpp.o.requires
	$(MAKE) -f src/pmidca/CMakeFiles/pmidca.dir/build.make src/pmidca/CMakeFiles/pmidca.dir/midca_Info.cpp.o.provides.build
.PHONY : src/pmidca/CMakeFiles/pmidca.dir/midca_Info.cpp.o.provides

src/pmidca/CMakeFiles/pmidca.dir/midca_Info.cpp.o.provides.build: src/pmidca/CMakeFiles/pmidca.dir/midca_Info.cpp.o


src/pmidca/CMakeFiles/pmidca.dir/main.cpp.o: src/pmidca/CMakeFiles/pmidca.dir/flags.make
src/pmidca/CMakeFiles/pmidca.dir/main.cpp.o: ../src/pmidca/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sampath/moos-ivp/moos-ivp-midca/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/pmidca/CMakeFiles/pmidca.dir/main.cpp.o"
	cd /home/sampath/moos-ivp/moos-ivp-midca/build/src/pmidca && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pmidca.dir/main.cpp.o -c /home/sampath/moos-ivp/moos-ivp-midca/src/pmidca/main.cpp

src/pmidca/CMakeFiles/pmidca.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pmidca.dir/main.cpp.i"
	cd /home/sampath/moos-ivp/moos-ivp-midca/build/src/pmidca && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sampath/moos-ivp/moos-ivp-midca/src/pmidca/main.cpp > CMakeFiles/pmidca.dir/main.cpp.i

src/pmidca/CMakeFiles/pmidca.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pmidca.dir/main.cpp.s"
	cd /home/sampath/moos-ivp/moos-ivp-midca/build/src/pmidca && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sampath/moos-ivp/moos-ivp-midca/src/pmidca/main.cpp -o CMakeFiles/pmidca.dir/main.cpp.s

src/pmidca/CMakeFiles/pmidca.dir/main.cpp.o.requires:

.PHONY : src/pmidca/CMakeFiles/pmidca.dir/main.cpp.o.requires

src/pmidca/CMakeFiles/pmidca.dir/main.cpp.o.provides: src/pmidca/CMakeFiles/pmidca.dir/main.cpp.o.requires
	$(MAKE) -f src/pmidca/CMakeFiles/pmidca.dir/build.make src/pmidca/CMakeFiles/pmidca.dir/main.cpp.o.provides.build
.PHONY : src/pmidca/CMakeFiles/pmidca.dir/main.cpp.o.provides

src/pmidca/CMakeFiles/pmidca.dir/main.cpp.o.provides.build: src/pmidca/CMakeFiles/pmidca.dir/main.cpp.o


# Object files for target pmidca
pmidca_OBJECTS = \
"CMakeFiles/pmidca.dir/midca.cpp.o" \
"CMakeFiles/pmidca.dir/midca_Info.cpp.o" \
"CMakeFiles/pmidca.dir/main.cpp.o"

# External object files for target pmidca
pmidca_EXTERNAL_OBJECTS =

../bin/pmidca: src/pmidca/CMakeFiles/pmidca.dir/midca.cpp.o
../bin/pmidca: src/pmidca/CMakeFiles/pmidca.dir/midca_Info.cpp.o
../bin/pmidca: src/pmidca/CMakeFiles/pmidca.dir/main.cpp.o
../bin/pmidca: src/pmidca/CMakeFiles/pmidca.dir/build.make
../bin/pmidca: /home/sampath/moos-ivp/build/MOOS/MOOSCore/lib/libMOOS.a
../bin/pmidca: /usr/lib/x86_64-linux-gnu/libzmq.so
../bin/pmidca: src/pmidca/CMakeFiles/pmidca.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sampath/moos-ivp/moos-ivp-midca/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ../../../bin/pmidca"
	cd /home/sampath/moos-ivp/moos-ivp-midca/build/src/pmidca && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pmidca.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/pmidca/CMakeFiles/pmidca.dir/build: ../bin/pmidca

.PHONY : src/pmidca/CMakeFiles/pmidca.dir/build

src/pmidca/CMakeFiles/pmidca.dir/requires: src/pmidca/CMakeFiles/pmidca.dir/midca.cpp.o.requires
src/pmidca/CMakeFiles/pmidca.dir/requires: src/pmidca/CMakeFiles/pmidca.dir/midca_Info.cpp.o.requires
src/pmidca/CMakeFiles/pmidca.dir/requires: src/pmidca/CMakeFiles/pmidca.dir/main.cpp.o.requires

.PHONY : src/pmidca/CMakeFiles/pmidca.dir/requires

src/pmidca/CMakeFiles/pmidca.dir/clean:
	cd /home/sampath/moos-ivp/moos-ivp-midca/build/src/pmidca && $(CMAKE_COMMAND) -P CMakeFiles/pmidca.dir/cmake_clean.cmake
.PHONY : src/pmidca/CMakeFiles/pmidca.dir/clean

src/pmidca/CMakeFiles/pmidca.dir/depend:
	cd /home/sampath/moos-ivp/moos-ivp-midca/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sampath/moos-ivp/moos-ivp-midca /home/sampath/moos-ivp/moos-ivp-midca/src/pmidca /home/sampath/moos-ivp/moos-ivp-midca/build /home/sampath/moos-ivp/moos-ivp-midca/build/src/pmidca /home/sampath/moos-ivp/moos-ivp-midca/build/src/pmidca/CMakeFiles/pmidca.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/pmidca/CMakeFiles/pmidca.dir/depend

