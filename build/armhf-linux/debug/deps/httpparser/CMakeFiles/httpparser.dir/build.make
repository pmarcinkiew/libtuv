# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /iotjs/deps/http-parser

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /iotjs/build/armhf-linux/debug/deps/httpparser

# Include any dependencies generated for this target.
include CMakeFiles/httpparser.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/httpparser.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/httpparser.dir/flags.make

CMakeFiles/httpparser.dir/http_parser.c.o: CMakeFiles/httpparser.dir/flags.make
CMakeFiles/httpparser.dir/http_parser.c.o: /iotjs/deps/http-parser/http_parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/iotjs/build/armhf-linux/debug/deps/httpparser/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/httpparser.dir/http_parser.c.o"
	/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/httpparser.dir/http_parser.c.o   -c /iotjs/deps/http-parser/http_parser.c

CMakeFiles/httpparser.dir/http_parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/httpparser.dir/http_parser.c.i"
	/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /iotjs/deps/http-parser/http_parser.c > CMakeFiles/httpparser.dir/http_parser.c.i

CMakeFiles/httpparser.dir/http_parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/httpparser.dir/http_parser.c.s"
	/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /iotjs/deps/http-parser/http_parser.c -o CMakeFiles/httpparser.dir/http_parser.c.s

CMakeFiles/httpparser.dir/http_parser.c.o.requires:

.PHONY : CMakeFiles/httpparser.dir/http_parser.c.o.requires

CMakeFiles/httpparser.dir/http_parser.c.o.provides: CMakeFiles/httpparser.dir/http_parser.c.o.requires
	$(MAKE) -f CMakeFiles/httpparser.dir/build.make CMakeFiles/httpparser.dir/http_parser.c.o.provides.build
.PHONY : CMakeFiles/httpparser.dir/http_parser.c.o.provides

CMakeFiles/httpparser.dir/http_parser.c.o.provides.build: CMakeFiles/httpparser.dir/http_parser.c.o


# Object files for target httpparser
httpparser_OBJECTS = \
"CMakeFiles/httpparser.dir/http_parser.c.o"

# External object files for target httpparser
httpparser_EXTERNAL_OBJECTS =

libhttpparser.a: CMakeFiles/httpparser.dir/http_parser.c.o
libhttpparser.a: CMakeFiles/httpparser.dir/build.make
libhttpparser.a: CMakeFiles/httpparser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/iotjs/build/armhf-linux/debug/deps/httpparser/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libhttpparser.a"
	$(CMAKE_COMMAND) -P CMakeFiles/httpparser.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/httpparser.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/httpparser.dir/build: libhttpparser.a

.PHONY : CMakeFiles/httpparser.dir/build

CMakeFiles/httpparser.dir/requires: CMakeFiles/httpparser.dir/http_parser.c.o.requires

.PHONY : CMakeFiles/httpparser.dir/requires

CMakeFiles/httpparser.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/httpparser.dir/cmake_clean.cmake
.PHONY : CMakeFiles/httpparser.dir/clean

CMakeFiles/httpparser.dir/depend:
	cd /iotjs/build/armhf-linux/debug/deps/httpparser && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /iotjs/deps/http-parser /iotjs/deps/http-parser /iotjs/build/armhf-linux/debug/deps/httpparser /iotjs/build/armhf-linux/debug/deps/httpparser /iotjs/build/armhf-linux/debug/deps/httpparser/CMakeFiles/httpparser.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/httpparser.dir/depend

