# The following just specifies some variables for "flexibility".

# Specify the C++ compiler
CXX     = g++

# Specify options to pass to the compiler. Here it sets the optimisation
# level, outputs debugging info for gdb, and C++ version to use.
CXXFLAGS = -O0 -g3 -std=c++17

All: all
all: main HybridTableTesterMain

main: main.cpp HybridTable.o
	$(CXX) $(CXXFLAGS) main.cpp HybridTable.o -o main

# The -c command produces the object file
HybridTable.o: HybridTable.cpp HybridTable.h
	$(CXX) $(CXXFLAGS) -c HybridTable.cpp -o HybridTable.o

HybridTableTesterMain: HybridTableTesterMain.cpp HybridTable.o HybridTableTester.o
	$(CXX) $(CXXFLAGS) HybridTableTesterMain.cpp HybridTable.o HybridTableTester.o -o HybridTableTesterMain

HybridTableTester.o: HybridTableTester.cpp HybridTableTester.h
	$(CXX) $(CXXFLAGS) -c HybridTableTester.cpp -o HybridTableTester.o

# Some cleanup functions, invoked by typing "make clean" or "make deepclean"
deepclean:
	rm -f *~ *.o HybridTableTesterMain main main.exe *.stackdump

clean:
	rm -f *~ *.o *.stackdump

