#include <iostream>
#include "HybridTableTester.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

	for(int i=1; i<argc; i++) {
		switch (argv[i][0]) {
		case 'a': { HybridTableTester t; t.testa(); } break;
		case 'b': { HybridTableTester t; t.testb(); } break;
		case 'c': { HybridTableTester t; t.testc(); } break;
		case 'd': { HybridTableTester t; t.testd(); } break;
		case 'e': { HybridTableTester t; t.teste(); } break;
		case 'f': { HybridTableTester t; t.testf(); } break;
		case 'g': { HybridTableTester t; t.testg(); } break;
		case 'h': { HybridTableTester t; t.testh(); } break;
		case 'i': { HybridTableTester t; t.testi(); } break;
		case 'j': { HybridTableTester t; t.testj(); } break;
		case 'k': { HybridTableTester t; t.testk(); } break;
		case 'l': { HybridTableTester t; t.testl(); } break;
		case 'm': { HybridTableTester t; t.testm(); } break;
		case 'n': { HybridTableTester t; t.testn(); } break;
		case 'o': { HybridTableTester t; t.testo(); } break;
		case 'p': { HybridTableTester t; t.testp(); } break;
		case 'q': { HybridTableTester t; t.testq(); } break;
		case 'r': { HybridTableTester t; t.testr(); } break;
		case 's': { HybridTableTester t; t.tests(); } break;
		case 't': { HybridTableTester t; t.testt(); } break;
		case 'u': { HybridTableTester t; t.testu(); } break;
		case 'v': { HybridTableTester t; t.testv(); } break;
		case 'w': { HybridTableTester t; t.testw(); } break;
		case 'x': { HybridTableTester t; t.testx(); } break;
		case 'y': { HybridTableTester t; t.testy(); } break;
		case 'z': { HybridTableTester t; t.testz(); } break;
		default: { cout << "Options are a -- y." << endl; } break;
	       	}
	}
	return 0;
}

