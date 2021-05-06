# Executable Name
EXENAME = finalproj
#include png/make/cs225.mk

# Object Types
OBJS = main.o readFromFile.o Node.o Edge.o Graph.o Airports.o BFS.o mapprinter.o

# Compilation Flags
CXX = clang++
CXXFLAGS = $(CS225) -Ics225 -std=c++14 -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = $(CS225) -Ics225 -std=c++14 -stdlib=libc++ -lc++abi -lm

# Custom Clang Enforcement
#include make/cs225.mk
include make/customClangEnforcement.mk
#include cs225/make/cs225.mk

# Define Makefile Rules
.PHONY: all test clean output_msg

all : $(EXENAME)

#output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o: main.cpp readFromFile.cpp Node.cpp Edge.cpp Graph.cpp Airports.cpp BFS.cpp mapprinter.cpp 
	$(CXX) $(CXXFLAGS) main.cpp readFromFile.cpp Node.cpp Edge.cpp Graph.cpp Airports.cpp BFS.cpp mapprinter.cpp

test: output_msg catch/catchmain.cpp tests/tests.cpp readFromFile.cpp Node.cpp Edge.cpp Graph.cpp Airports.cpp BFS.cpp mapprinter.cpp
	$(LD) $(LDFLAGS) catch/catchmain.cpp tests/tests.cpp cs225/lodepng/lodepng.cpp cs225/PNG.cpp cs225/HSLAPixel.cpp readFromFile.cpp Node.cpp Edge.cpp Graph.cpp Airports.cpp BFS.cpp mapprinter.cpp $(LDFLAGS) -o test

include cs225/make/cs225.mk

#clean:
#	-rm -f *.o $(EXENAME) test