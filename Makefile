# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/gres2/SP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gres2/SP/cmake-build-debug

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/gres2/SP/cmake-build-debug/CMakeFiles /home/gres2/SP/cmake-build-debug//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/gres2/SP/cmake-build-debug/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Clovece

# Build rule for target.
Clovece: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 Clovece
.PHONY : Clovece

# fast build rule for target.
Clovece/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/build
.PHONY : Clovece/fast

debug_leaks/debug_new.o: debug_leaks/debug_new.cpp.o

.PHONY : debug_leaks/debug_new.o

# target to build an object file
debug_leaks/debug_new.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/debug_leaks/debug_new.cpp.o
.PHONY : debug_leaks/debug_new.cpp.o

debug_leaks/debug_new.i: debug_leaks/debug_new.cpp.i

.PHONY : debug_leaks/debug_new.i

# target to preprocess a source file
debug_leaks/debug_new.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/debug_leaks/debug_new.cpp.i
.PHONY : debug_leaks/debug_new.cpp.i

debug_leaks/debug_new.s: debug_leaks/debug_new.cpp.s

.PHONY : debug_leaks/debug_new.s

# target to generate assembly for a file
debug_leaks/debug_new.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/debug_leaks/debug_new.cpp.s
.PHONY : debug_leaks/debug_new.cpp.s

game/Clovece.o: game/Clovece.cpp.o

.PHONY : game/Clovece.o

# target to build an object file
game/Clovece.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/game/Clovece.cpp.o
.PHONY : game/Clovece.cpp.o

game/Clovece.i: game/Clovece.cpp.i

.PHONY : game/Clovece.i

# target to preprocess a source file
game/Clovece.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/game/Clovece.cpp.i
.PHONY : game/Clovece.cpp.i

game/Clovece.s: game/Clovece.cpp.s

.PHONY : game/Clovece.s

# target to generate assembly for a file
game/Clovece.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/game/Clovece.cpp.s
.PHONY : game/Clovece.cpp.s

game/Player.o: game/Player.cpp.o

.PHONY : game/Player.o

# target to build an object file
game/Player.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/game/Player.cpp.o
.PHONY : game/Player.cpp.o

game/Player.i: game/Player.cpp.i

.PHONY : game/Player.i

# target to preprocess a source file
game/Player.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/game/Player.cpp.i
.PHONY : game/Player.cpp.i

game/Player.s: game/Player.cpp.s

.PHONY : game/Player.s

# target to generate assembly for a file
game/Player.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/game/Player.cpp.s
.PHONY : game/Player.cpp.s

game/board/Board.o: game/board/Board.cpp.o

.PHONY : game/board/Board.o

# target to build an object file
game/board/Board.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/game/board/Board.cpp.o
.PHONY : game/board/Board.cpp.o

game/board/Board.i: game/board/Board.cpp.i

.PHONY : game/board/Board.i

# target to preprocess a source file
game/board/Board.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/game/board/Board.cpp.i
.PHONY : game/board/Board.cpp.i

game/board/Board.s: game/board/Board.cpp.s

.PHONY : game/board/Board.s

# target to generate assembly for a file
game/board/Board.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/game/board/Board.cpp.s
.PHONY : game/board/Board.cpp.s

game/board/Circle.o: game/board/Circle.cpp.o

.PHONY : game/board/Circle.o

# target to build an object file
game/board/Circle.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/game/board/Circle.cpp.o
.PHONY : game/board/Circle.cpp.o

game/board/Circle.i: game/board/Circle.cpp.i

.PHONY : game/board/Circle.i

# target to preprocess a source file
game/board/Circle.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/game/board/Circle.cpp.i
.PHONY : game/board/Circle.cpp.i

game/board/Circle.s: game/board/Circle.cpp.s

.PHONY : game/board/Circle.s

# target to generate assembly for a file
game/board/Circle.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/game/board/Circle.cpp.s
.PHONY : game/board/Circle.cpp.s

game/board/Figure.o: game/board/Figure.cpp.o

.PHONY : game/board/Figure.o

# target to build an object file
game/board/Figure.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/game/board/Figure.cpp.o
.PHONY : game/board/Figure.cpp.o

game/board/Figure.i: game/board/Figure.cpp.i

.PHONY : game/board/Figure.i

# target to preprocess a source file
game/board/Figure.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/game/board/Figure.cpp.i
.PHONY : game/board/Figure.cpp.i

game/board/Figure.s: game/board/Figure.cpp.s

.PHONY : game/board/Figure.s

# target to generate assembly for a file
game/board/Figure.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/game/board/Figure.cpp.s
.PHONY : game/board/Figure.cpp.s

game/network/Connection.o: game/network/Connection.cpp.o

.PHONY : game/network/Connection.o

# target to build an object file
game/network/Connection.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/game/network/Connection.cpp.o
.PHONY : game/network/Connection.cpp.o

game/network/Connection.i: game/network/Connection.cpp.i

.PHONY : game/network/Connection.i

# target to preprocess a source file
game/network/Connection.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/game/network/Connection.cpp.i
.PHONY : game/network/Connection.cpp.i

game/network/Connection.s: game/network/Connection.cpp.s

.PHONY : game/network/Connection.s

# target to generate assembly for a file
game/network/Connection.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/game/network/Connection.cpp.s
.PHONY : game/network/Connection.cpp.s

game/network/Move.o: game/network/Move.cpp.o

.PHONY : game/network/Move.o

# target to build an object file
game/network/Move.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/game/network/Move.cpp.o
.PHONY : game/network/Move.cpp.o

game/network/Move.i: game/network/Move.cpp.i

.PHONY : game/network/Move.i

# target to preprocess a source file
game/network/Move.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/game/network/Move.cpp.i
.PHONY : game/network/Move.cpp.i

game/network/Move.s: game/network/Move.cpp.s

.PHONY : game/network/Move.s

# target to generate assembly for a file
game/network/Move.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/game/network/Move.cpp.s
.PHONY : game/network/Move.cpp.s

graphic/Graphic.o: graphic/Graphic.cpp.o

.PHONY : graphic/Graphic.o

# target to build an object file
graphic/Graphic.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/graphic/Graphic.cpp.o
.PHONY : graphic/Graphic.cpp.o

graphic/Graphic.i: graphic/Graphic.cpp.i

.PHONY : graphic/Graphic.i

# target to preprocess a source file
graphic/Graphic.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/graphic/Graphic.cpp.i
.PHONY : graphic/Graphic.cpp.i

graphic/Graphic.s: graphic/Graphic.cpp.s

.PHONY : graphic/Graphic.s

# target to generate assembly for a file
graphic/Graphic.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/graphic/Graphic.cpp.s
.PHONY : graphic/Graphic.cpp.s

graphic/Settings.o: graphic/Settings.cpp.o

.PHONY : graphic/Settings.o

# target to build an object file
graphic/Settings.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/graphic/Settings.cpp.o
.PHONY : graphic/Settings.cpp.o

graphic/Settings.i: graphic/Settings.cpp.i

.PHONY : graphic/Settings.i

# target to preprocess a source file
graphic/Settings.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/graphic/Settings.cpp.i
.PHONY : graphic/Settings.cpp.i

graphic/Settings.s: graphic/Settings.cpp.s

.PHONY : graphic/Settings.s

# target to generate assembly for a file
graphic/Settings.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/graphic/Settings.cpp.s
.PHONY : graphic/Settings.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Clovece.dir/build.make CMakeFiles/Clovece.dir/main.cpp.s
.PHONY : main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... Clovece"
	@echo "... debug_leaks/debug_new.o"
	@echo "... debug_leaks/debug_new.i"
	@echo "... debug_leaks/debug_new.s"
	@echo "... game/Clovece.o"
	@echo "... game/Clovece.i"
	@echo "... game/Clovece.s"
	@echo "... game/Player.o"
	@echo "... game/Player.i"
	@echo "... game/Player.s"
	@echo "... game/board/Board.o"
	@echo "... game/board/Board.i"
	@echo "... game/board/Board.s"
	@echo "... game/board/Circle.o"
	@echo "... game/board/Circle.i"
	@echo "... game/board/Circle.s"
	@echo "... game/board/Figure.o"
	@echo "... game/board/Figure.i"
	@echo "... game/board/Figure.s"
	@echo "... game/network/Connection.o"
	@echo "... game/network/Connection.i"
	@echo "... game/network/Connection.s"
	@echo "... game/network/Move.o"
	@echo "... game/network/Move.i"
	@echo "... game/network/Move.s"
	@echo "... graphic/Graphic.o"
	@echo "... graphic/Graphic.i"
	@echo "... graphic/Graphic.s"
	@echo "... graphic/Settings.o"
	@echo "... graphic/Settings.i"
	@echo "... graphic/Settings.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

