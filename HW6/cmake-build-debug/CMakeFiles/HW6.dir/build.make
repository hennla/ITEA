# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.1.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.1.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\GIT\ITEA\HW6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\GIT\ITEA\HW6\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/HW6.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/HW6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HW6.dir/flags.make

CMakeFiles/HW6.dir/main.cpp.obj: CMakeFiles/HW6.dir/flags.make
CMakeFiles/HW6.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\GIT\ITEA\HW6\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HW6.dir/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\HW6.dir\main.cpp.obj -c D:\GIT\ITEA\HW6\main.cpp

CMakeFiles/HW6.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HW6.dir/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\GIT\ITEA\HW6\main.cpp > CMakeFiles\HW6.dir\main.cpp.i

CMakeFiles/HW6.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HW6.dir/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\GIT\ITEA\HW6\main.cpp -o CMakeFiles\HW6.dir\main.cpp.s

# Object files for target HW6
HW6_OBJECTS = \
"CMakeFiles/HW6.dir/main.cpp.obj"

# External object files for target HW6
HW6_EXTERNAL_OBJECTS =

HW6.exe: CMakeFiles/HW6.dir/main.cpp.obj
HW6.exe: CMakeFiles/HW6.dir/build.make
HW6.exe: CMakeFiles/HW6.dir/linklibs.rsp
HW6.exe: CMakeFiles/HW6.dir/objects1.rsp
HW6.exe: CMakeFiles/HW6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\GIT\ITEA\HW6\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HW6.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\HW6.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HW6.dir/build: HW6.exe
.PHONY : CMakeFiles/HW6.dir/build

CMakeFiles/HW6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\HW6.dir\cmake_clean.cmake
.PHONY : CMakeFiles/HW6.dir/clean

CMakeFiles/HW6.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\GIT\ITEA\HW6 D:\GIT\ITEA\HW6 D:\GIT\ITEA\HW6\cmake-build-debug D:\GIT\ITEA\HW6\cmake-build-debug D:\GIT\ITEA\HW6\cmake-build-debug\CMakeFiles\HW6.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HW6.dir/depend
