# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

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
CMAKE_SOURCE_DIR = D:\GIT\ITEA\HW1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\GIT\ITEA\HW1\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/HW1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HW1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HW1.dir/flags.make

CMakeFiles/HW1.dir/main.cpp.obj: CMakeFiles/HW1.dir/flags.make
CMakeFiles/HW1.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\GIT\ITEA\HW1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HW1.dir/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\HW1.dir\main.cpp.obj -c D:\GIT\ITEA\HW1\main.cpp

CMakeFiles/HW1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HW1.dir/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\GIT\ITEA\HW1\main.cpp > CMakeFiles\HW1.dir\main.cpp.i

CMakeFiles/HW1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HW1.dir/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\GIT\ITEA\HW1\main.cpp -o CMakeFiles\HW1.dir\main.cpp.s

# Object files for target HW1
HW1_OBJECTS = \
"CMakeFiles/HW1.dir/main.cpp.obj"

# External object files for target HW1
HW1_EXTERNAL_OBJECTS =

HW1.exe: CMakeFiles/HW1.dir/main.cpp.obj
HW1.exe: CMakeFiles/HW1.dir/build.make
HW1.exe: CMakeFiles/HW1.dir/linklibs.rsp
HW1.exe: CMakeFiles/HW1.dir/objects1.rsp
HW1.exe: CMakeFiles/HW1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\GIT\ITEA\HW1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HW1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\HW1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HW1.dir/build: HW1.exe

.PHONY : CMakeFiles/HW1.dir/build

CMakeFiles/HW1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\HW1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/HW1.dir/clean

CMakeFiles/HW1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\GIT\ITEA\HW1 D:\GIT\ITEA\HW1 D:\GIT\ITEA\HW1\cmake-build-debug D:\GIT\ITEA\HW1\cmake-build-debug D:\GIT\ITEA\HW1\cmake-build-debug\CMakeFiles\HW1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HW1.dir/depend

