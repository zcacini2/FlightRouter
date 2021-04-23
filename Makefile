# Executable Name
EXENAME = finalproj

# Object Types
OBJS = main.o readFromFile.o Node.o Edge.o Graph.o Airports.o BFS.o

# Compilation Flags
CXX = clang++
CXXFLAGS = $(CS225) -std=c++14 -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic -Wno-address-of-temporary
LD = clang++
LDFLAGS = -std=c++14 -stdlib=libc++ -lc++abi -lm

# Custom Clang Enforcement
include make/customClangEnforcement.mk

# Define Makefile Rules
.PHONY: all test clean output_msg

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o: main.cpp readFromFile.cpp Node.cpp Edge.cpp Graph.cpp Airports.cpp BFS.cpp
	$(CXX) $(CXXFLAGS) main.cpp readFromFile.cpp Node.cpp Edge.cpp Graph.cpp Airports.cpp BFS.cpp

test: output_msg catch/catchmain.cpp tests/tests.cpp readFromFile.cpp Node.cpp Edge.cpp Graph.cpp Airports.cpp BFS.cpp
	$(LD) -Wno-address-of-temporary catch/catchmain.cpp tests/tests.cpp readFromFile.cpp Node.cpp Edge.cpp Graph.cpp Airports.cpp BFS.cpp $(LDFLAGS) -o test

clean:
	-rm -f *.o $(EXENAME) test