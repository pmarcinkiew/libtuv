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
CMAKE_SOURCE_DIR = /iotjs/deps/jerry

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /iotjs/build/host/x86_64-linux/debug/deps/jerry

# Include any dependencies generated for this target.
include jerry-libc/CMakeFiles/jerry-libc.dir/depend.make

# Include the progress variables for this target.
include jerry-libc/CMakeFiles/jerry-libc.dir/progress.make

# Include the compile flags for this target's objects.
include jerry-libc/CMakeFiles/jerry-libc.dir/flags.make

jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc-printf.c.o: jerry-libc/CMakeFiles/jerry-libc.dir/flags.make
jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc-printf.c.o: /iotjs/deps/jerry/jerry-libc/jerry-libc-printf.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/iotjs/build/host/x86_64-linux/debug/deps/jerry/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc-printf.c.o"
	cd /iotjs/build/host/x86_64-linux/debug/deps/jerry/jerry-libc && /tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/jerry-libc.dir/jerry-libc-printf.c.o   -c /iotjs/deps/jerry/jerry-libc/jerry-libc-printf.c

jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc-printf.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/jerry-libc.dir/jerry-libc-printf.c.i"
	cd /iotjs/build/host/x86_64-linux/debug/deps/jerry/jerry-libc && /tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /iotjs/deps/jerry/jerry-libc/jerry-libc-printf.c > CMakeFiles/jerry-libc.dir/jerry-libc-printf.c.i

jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc-printf.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/jerry-libc.dir/jerry-libc-printf.c.s"
	cd /iotjs/build/host/x86_64-linux/debug/deps/jerry/jerry-libc && /tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /iotjs/deps/jerry/jerry-libc/jerry-libc-printf.c -o CMakeFiles/jerry-libc.dir/jerry-libc-printf.c.s

jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc-printf.c.o.requires:

.PHONY : jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc-printf.c.o.requires

jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc-printf.c.o.provides: jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc-printf.c.o.requires
	$(MAKE) -f jerry-libc/CMakeFiles/jerry-libc.dir/build.make jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc-printf.c.o.provides.build
.PHONY : jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc-printf.c.o.provides

jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc-printf.c.o.provides.build: jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc-printf.c.o


jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc.c.o: jerry-libc/CMakeFiles/jerry-libc.dir/flags.make
jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc.c.o: /iotjs/deps/jerry/jerry-libc/jerry-libc.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/iotjs/build/host/x86_64-linux/debug/deps/jerry/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc.c.o"
	cd /iotjs/build/host/x86_64-linux/debug/deps/jerry/jerry-libc && /tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/jerry-libc.dir/jerry-libc.c.o   -c /iotjs/deps/jerry/jerry-libc/jerry-libc.c

jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/jerry-libc.dir/jerry-libc.c.i"
	cd /iotjs/build/host/x86_64-linux/debug/deps/jerry/jerry-libc && /tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /iotjs/deps/jerry/jerry-libc/jerry-libc.c > CMakeFiles/jerry-libc.dir/jerry-libc.c.i

jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/jerry-libc.dir/jerry-libc.c.s"
	cd /iotjs/build/host/x86_64-linux/debug/deps/jerry/jerry-libc && /tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /iotjs/deps/jerry/jerry-libc/jerry-libc.c -o CMakeFiles/jerry-libc.dir/jerry-libc.c.s

jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc.c.o.requires:

.PHONY : jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc.c.o.requires

jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc.c.o.provides: jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc.c.o.requires
	$(MAKE) -f jerry-libc/CMakeFiles/jerry-libc.dir/build.make jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc.c.o.provides.build
.PHONY : jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc.c.o.provides

jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc.c.o.provides.build: jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc.c.o


jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-libc-target.c.o: jerry-libc/CMakeFiles/jerry-libc.dir/flags.make
jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-libc-target.c.o: /iotjs/deps/jerry/jerry-libc/target/posix/jerry-libc-target.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/iotjs/build/host/x86_64-linux/debug/deps/jerry/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-libc-target.c.o"
	cd /iotjs/build/host/x86_64-linux/debug/deps/jerry/jerry-libc && /tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/jerry-libc.dir/target/posix/jerry-libc-target.c.o   -c /iotjs/deps/jerry/jerry-libc/target/posix/jerry-libc-target.c

jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-libc-target.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/jerry-libc.dir/target/posix/jerry-libc-target.c.i"
	cd /iotjs/build/host/x86_64-linux/debug/deps/jerry/jerry-libc && /tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /iotjs/deps/jerry/jerry-libc/target/posix/jerry-libc-target.c > CMakeFiles/jerry-libc.dir/target/posix/jerry-libc-target.c.i

jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-libc-target.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/jerry-libc.dir/target/posix/jerry-libc-target.c.s"
	cd /iotjs/build/host/x86_64-linux/debug/deps/jerry/jerry-libc && /tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /iotjs/deps/jerry/jerry-libc/target/posix/jerry-libc-target.c -o CMakeFiles/jerry-libc.dir/target/posix/jerry-libc-target.c.s

jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-libc-target.c.o.requires:

.PHONY : jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-libc-target.c.o.requires

jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-libc-target.c.o.provides: jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-libc-target.c.o.requires
	$(MAKE) -f jerry-libc/CMakeFiles/jerry-libc.dir/build.make jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-libc-target.c.o.provides.build
.PHONY : jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-libc-target.c.o.provides

jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-libc-target.c.o.provides.build: jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-libc-target.c.o


jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-asm.S.o: jerry-libc/CMakeFiles/jerry-libc.dir/flags.make
jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-asm.S.o: /iotjs/deps/jerry/jerry-libc/target/posix/jerry-asm.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/iotjs/build/host/x86_64-linux/debug/deps/jerry/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building ASM object jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-asm.S.o"
	cd /iotjs/build/host/x86_64-linux/debug/deps/jerry/jerry-libc && /tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/arm-linux-gnueabihf-gcc  $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/jerry-libc.dir/target/posix/jerry-asm.S.o -c /iotjs/deps/jerry/jerry-libc/target/posix/jerry-asm.S

jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-asm.S.o.requires:

.PHONY : jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-asm.S.o.requires

jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-asm.S.o.provides: jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-asm.S.o.requires
	$(MAKE) -f jerry-libc/CMakeFiles/jerry-libc.dir/build.make jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-asm.S.o.provides.build
.PHONY : jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-asm.S.o.provides

jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-asm.S.o.provides.build: jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-asm.S.o


# Object files for target jerry-libc
jerry__libc_OBJECTS = \
"CMakeFiles/jerry-libc.dir/jerry-libc-printf.c.o" \
"CMakeFiles/jerry-libc.dir/jerry-libc.c.o" \
"CMakeFiles/jerry-libc.dir/target/posix/jerry-libc-target.c.o" \
"CMakeFiles/jerry-libc.dir/target/posix/jerry-asm.S.o"

# External object files for target jerry-libc
jerry__libc_EXTERNAL_OBJECTS =

lib/libjerry-libc.a: jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc-printf.c.o
lib/libjerry-libc.a: jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc.c.o
lib/libjerry-libc.a: jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-libc-target.c.o
lib/libjerry-libc.a: jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-asm.S.o
lib/libjerry-libc.a: jerry-libc/CMakeFiles/jerry-libc.dir/build.make
lib/libjerry-libc.a: jerry-libc/CMakeFiles/jerry-libc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/iotjs/build/host/x86_64-linux/debug/deps/jerry/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C static library ../lib/libjerry-libc.a"
	cd /iotjs/build/host/x86_64-linux/debug/deps/jerry/jerry-libc && $(CMAKE_COMMAND) -P CMakeFiles/jerry-libc.dir/cmake_clean_target.cmake
	cd /iotjs/build/host/x86_64-linux/debug/deps/jerry/jerry-libc && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jerry-libc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
jerry-libc/CMakeFiles/jerry-libc.dir/build: lib/libjerry-libc.a

.PHONY : jerry-libc/CMakeFiles/jerry-libc.dir/build

jerry-libc/CMakeFiles/jerry-libc.dir/requires: jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc-printf.c.o.requires
jerry-libc/CMakeFiles/jerry-libc.dir/requires: jerry-libc/CMakeFiles/jerry-libc.dir/jerry-libc.c.o.requires
jerry-libc/CMakeFiles/jerry-libc.dir/requires: jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-libc-target.c.o.requires
jerry-libc/CMakeFiles/jerry-libc.dir/requires: jerry-libc/CMakeFiles/jerry-libc.dir/target/posix/jerry-asm.S.o.requires

.PHONY : jerry-libc/CMakeFiles/jerry-libc.dir/requires

jerry-libc/CMakeFiles/jerry-libc.dir/clean:
	cd /iotjs/build/host/x86_64-linux/debug/deps/jerry/jerry-libc && $(CMAKE_COMMAND) -P CMakeFiles/jerry-libc.dir/cmake_clean.cmake
.PHONY : jerry-libc/CMakeFiles/jerry-libc.dir/clean

jerry-libc/CMakeFiles/jerry-libc.dir/depend:
	cd /iotjs/build/host/x86_64-linux/debug/deps/jerry && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /iotjs/deps/jerry /iotjs/deps/jerry/jerry-libc /iotjs/build/host/x86_64-linux/debug/deps/jerry /iotjs/build/host/x86_64-linux/debug/deps/jerry/jerry-libc /iotjs/build/host/x86_64-linux/debug/deps/jerry/jerry-libc/CMakeFiles/jerry-libc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : jerry-libc/CMakeFiles/jerry-libc.dir/depend

