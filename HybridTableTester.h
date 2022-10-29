#ifndef HYBRIDTABLETESTER_H_
#define HYBRIDTABLETESTER_H_

#include <string>
#include "HybridTable.h"

class HybridTableTester {
public:
	HybridTableTester();

	// getarraysize, gettotalsize, dtor req'd throughout

	// ctor
	void testa();
	void testb();

	// get/set
	void testc();
	void testd();
	void teste();
	void testf();
	void testg();
	void testh();

	// toString
	void testi();
	void testj();
	void testk();
	void testl();
	void testm();

	// copy con, asg
	void testn();
	void testo();
	void testp();
	void testq();
	void testr();
	void tests();

	// resize
	void testt();
	void testu();
	void testv();
	void testw();
	void testx();
	void testy();

	// unused
	void testz();

private:

	// three overloaded versions
	void errorOut_(const std::string& errMsg, unsigned int errBit);
	void errorOut_(const std::string& errMsg, const std::string& errRes, unsigned int errBit);
	void errorOut_(const std::string& errMsg, int errRes, unsigned int errBit);
	void passOut_();

	char error_;
	std::string funcname_;
};

#endif /* HYBRIDTABLETESTER_H_ */
