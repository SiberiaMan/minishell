# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/dchani/Desktop/project/Misha

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/dchani/Desktop/project/Misha/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/shell.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/shell.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/shell.dir/flags.make

CMakeFiles/shell.dir/backslash.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/backslash.c.o: ../backslash.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dchani/Desktop/project/Misha/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/shell.dir/backslash.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shell.dir/backslash.c.o -c /Users/dchani/Desktop/project/Misha/backslash.c

CMakeFiles/shell.dir/backslash.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/backslash.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dchani/Desktop/project/Misha/backslash.c > CMakeFiles/shell.dir/backslash.c.i

CMakeFiles/shell.dir/backslash.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/backslash.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dchani/Desktop/project/Misha/backslash.c -o CMakeFiles/shell.dir/backslash.c.s

CMakeFiles/shell.dir/pretokenizer_handler.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/pretokenizer_handler.c.o: ../pretokenizer_handler.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dchani/Desktop/project/Misha/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/shell.dir/pretokenizer_handler.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shell.dir/pretokenizer_handler.c.o -c /Users/dchani/Desktop/project/Misha/pretokenizer_handler.c

CMakeFiles/shell.dir/pretokenizer_handler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/pretokenizer_handler.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dchani/Desktop/project/Misha/pretokenizer_handler.c > CMakeFiles/shell.dir/pretokenizer_handler.c.i

CMakeFiles/shell.dir/pretokenizer_handler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/pretokenizer_handler.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dchani/Desktop/project/Misha/pretokenizer_handler.c -o CMakeFiles/shell.dir/pretokenizer_handler.c.s

CMakeFiles/shell.dir/libft_utills.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/libft_utills.c.o: ../libft_utills.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dchani/Desktop/project/Misha/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/shell.dir/libft_utills.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shell.dir/libft_utills.c.o -c /Users/dchani/Desktop/project/Misha/libft_utills.c

CMakeFiles/shell.dir/libft_utills.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/libft_utills.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dchani/Desktop/project/Misha/libft_utills.c > CMakeFiles/shell.dir/libft_utills.c.i

CMakeFiles/shell.dir/libft_utills.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/libft_utills.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dchani/Desktop/project/Misha/libft_utills.c -o CMakeFiles/shell.dir/libft_utills.c.s

CMakeFiles/shell.dir/quotes_handler.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/quotes_handler.c.o: ../quotes_handler.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dchani/Desktop/project/Misha/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/shell.dir/quotes_handler.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shell.dir/quotes_handler.c.o -c /Users/dchani/Desktop/project/Misha/quotes_handler.c

CMakeFiles/shell.dir/quotes_handler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/quotes_handler.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dchani/Desktop/project/Misha/quotes_handler.c > CMakeFiles/shell.dir/quotes_handler.c.i

CMakeFiles/shell.dir/quotes_handler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/quotes_handler.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dchani/Desktop/project/Misha/quotes_handler.c -o CMakeFiles/shell.dir/quotes_handler.c.s

CMakeFiles/shell.dir/parser.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/parser.c.o: ../parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dchani/Desktop/project/Misha/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/shell.dir/parser.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shell.dir/parser.c.o -c /Users/dchani/Desktop/project/Misha/parser.c

CMakeFiles/shell.dir/parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/parser.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dchani/Desktop/project/Misha/parser.c > CMakeFiles/shell.dir/parser.c.i

CMakeFiles/shell.dir/parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/parser.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dchani/Desktop/project/Misha/parser.c -o CMakeFiles/shell.dir/parser.c.s

CMakeFiles/shell.dir/syntax_err.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/syntax_err.c.o: ../syntax_err.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dchani/Desktop/project/Misha/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/shell.dir/syntax_err.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shell.dir/syntax_err.c.o -c /Users/dchani/Desktop/project/Misha/syntax_err.c

CMakeFiles/shell.dir/syntax_err.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/syntax_err.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dchani/Desktop/project/Misha/syntax_err.c > CMakeFiles/shell.dir/syntax_err.c.i

CMakeFiles/shell.dir/syntax_err.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/syntax_err.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dchani/Desktop/project/Misha/syntax_err.c -o CMakeFiles/shell.dir/syntax_err.c.s

CMakeFiles/shell.dir/tokenizer_functions.c.o: CMakeFiles/shell.dir/flags.make
CMakeFiles/shell.dir/tokenizer_functions.c.o: ../tokenizer_functions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dchani/Desktop/project/Misha/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/shell.dir/tokenizer_functions.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/shell.dir/tokenizer_functions.c.o -c /Users/dchani/Desktop/project/Misha/tokenizer_functions.c

CMakeFiles/shell.dir/tokenizer_functions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/shell.dir/tokenizer_functions.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/dchani/Desktop/project/Misha/tokenizer_functions.c > CMakeFiles/shell.dir/tokenizer_functions.c.i

CMakeFiles/shell.dir/tokenizer_functions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/shell.dir/tokenizer_functions.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/dchani/Desktop/project/Misha/tokenizer_functions.c -o CMakeFiles/shell.dir/tokenizer_functions.c.s

# Object files for target shell
shell_OBJECTS = \
"CMakeFiles/shell.dir/backslash.c.o" \
"CMakeFiles/shell.dir/pretokenizer_handler.c.o" \
"CMakeFiles/shell.dir/libft_utills.c.o" \
"CMakeFiles/shell.dir/quotes_handler.c.o" \
"CMakeFiles/shell.dir/parser.c.o" \
"CMakeFiles/shell.dir/syntax_err.c.o" \
"CMakeFiles/shell.dir/tokenizer_functions.c.o"

# External object files for target shell
shell_EXTERNAL_OBJECTS =

shell: CMakeFiles/shell.dir/backslash.c.o
shell: CMakeFiles/shell.dir/pretokenizer_handler.c.o
shell: CMakeFiles/shell.dir/libft_utills.c.o
shell: CMakeFiles/shell.dir/quotes_handler.c.o
shell: CMakeFiles/shell.dir/parser.c.o
shell: CMakeFiles/shell.dir/syntax_err.c.o
shell: CMakeFiles/shell.dir/tokenizer_functions.c.o
shell: CMakeFiles/shell.dir/build.make
shell: CMakeFiles/shell.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/dchani/Desktop/project/Misha/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C executable shell"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shell.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/shell.dir/build: shell

.PHONY : CMakeFiles/shell.dir/build

CMakeFiles/shell.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/shell.dir/cmake_clean.cmake
.PHONY : CMakeFiles/shell.dir/clean

CMakeFiles/shell.dir/depend:
	cd /Users/dchani/Desktop/project/Misha/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/dchani/Desktop/project/Misha /Users/dchani/Desktop/project/Misha /Users/dchani/Desktop/project/Misha/cmake-build-debug /Users/dchani/Desktop/project/Misha/cmake-build-debug /Users/dchani/Desktop/project/Misha/cmake-build-debug/CMakeFiles/shell.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/shell.dir/depend

