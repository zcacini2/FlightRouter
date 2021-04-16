# Executable Name
EXENAME = finalproj
TEST = test

# Object Types
EXE_OBJ = main.o
OBJS = main.o readFromFile.o Node.o Edge.o 


# Compilation Flags
CXX = clang++
CXXFLAGS = $(CS225) -std=c++14 -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
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

main.o: readFromFile.cpp Node.cpp Edge.cpp Graph.cpp
	$(CXX) $(CXXFLAGS) readFromFile.cpp Node.cpp Edge.cpp Graph.cpp

test: output_msg catch/catchmain.cpp tests/tests.cpp readFromFile.cpp
	$(LD) catch/catchmain.cpp tests/tests.cpp readFromFile.cpp Node.cpp Edge.cpp Graph.cpp $(LDFLAGS) -o test

clean:
	-rm -f *.o $(EXENAME) test

#include cs225/make/cs225.mk
