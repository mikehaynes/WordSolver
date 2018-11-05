# Compiler
CXX = g++

# Flags
FLAGS = --std=c++17 -Wall -Werror -pedantic

# Regular Compile
REG = -O3

# Debug Compile
DEBUG = -g3

WordSolver: *.cpp
	$(CXX) $(FLAGS) $(REG) $^ -o $@

debug: *.cpp
	$(CXX) $(FLAGS) $(DEBUG) $^ -o WordSolver_debug

.PHONY: clean
clean:
	-rm -f WordSolver*
