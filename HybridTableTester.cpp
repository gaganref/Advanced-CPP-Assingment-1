#include <iostream>
#include <climits>
#include "HybridTableTester.h"
#include "HybridTable.h"

using namespace std;

HybridTableTester::HybridTableTester() : error_(false), funcname_("") {}

// def ctor
void HybridTableTester::testa() {
	funcname_ = "HybridTableTester::testa";
	{

	HybridTable t;
	if (t.getArraySize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("def ctor wrong arraysize: ", t.getArraySize(), 1);
	if (t.getTotalSize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("def ctor wrong totalsize: ", t.getTotalSize(), 1);

	for(int i = 0; i < HybridTable::INITIAL_ARRAY_SIZE; i++)
		if (t.get(i) != 0)
			errorOut_("def ctor not initialised to 0", 2);

	}
	passOut_();
}

// param ctor, non-power-2
void HybridTableTester::testb() {
	funcname_ = "HybridTableTester::testb";
	{

	const int n = 10;
	const int a[] = {0,1,2,3,4,5,6,7,8,9};
	HybridTable t(a, n);
	if (t.getArraySize() != n)
		errorOut_("param ctor wrong arraysize: ", t.getArraySize(), 1);
	if (t.getTotalSize() != n)
		errorOut_("param ctor wrong totalsize: ", t.getTotalSize(), 1);

	for(int i = 0; i < n; i++)
		if (t.get(i) != a[i])
			errorOut_("param ctor not initialised to a", 2);

	}
	passOut_();
}

// get/set array part: basic
void HybridTableTester::testc() {
	funcname_ = "HybridTableTester::testc";
	{

	HybridTable t;
	for(int i = 0; i < HybridTable::INITIAL_ARRAY_SIZE; i++)
		t.set(i, i*i);

	for(int i = 0; i < HybridTable::INITIAL_ARRAY_SIZE; i++)
		if (t.get(i) != i*i)
			errorOut_("get" + std::to_string(i) + " wrong: ", t.get(i), 1);

	if (t.getArraySize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("wrongly changed arraysize: ", t.getArraySize(), 2);
	if (t.getTotalSize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("wrongly changed totalsize: ", t.getTotalSize(), 2);

	}
	passOut_();
}

// get/set array part: param ctor, overwrite, different order etc
void HybridTableTester::testd() {
	funcname_ = "HybridTableTester::testd";
	{

	const int n = 10;
	int a[n] = {0};
	HybridTable t(a, n);
	for(int i = n-1; i >= 0; i--) {
		a[i] = i+1;
		t.set(i, i+1);
	}
	for(int i = 0; i < n; i++)
		if (t.get(i) != a[i])
			errorOut_("get" + std::to_string(i) + " wrong: ", t.get(i), 1);

	for(int i = 0; i < n; i+=2) {
		a[i] = 10*i;
		t.set(i, 10*i);
	}
	for(int i = 0; i < n; i++)
		if (t.get(i) != a[i])
			errorOut_("get" + std::to_string(i) + " wrong: ", t.get(i), 2);

	if (t.getArraySize() != n)
		errorOut_("wrong arraysize: ", t.getArraySize(), 2);
	if (t.getTotalSize() != n)
		errorOut_("wrong totalsize: ", t.getTotalSize(), 2);

	}
	passOut_();
}

// get/set list part: first item; another item after
void HybridTableTester::teste() {
	funcname_ = "HybridTableTester::teste";
	{

	HybridTable t;
	t.set(100,1);
	if (t.get(100) != 1) errorOut_("get100 wrong: ", t.get(100), 1);

	t.set(200,2);
	if (t.get(200) != 2) errorOut_("get200 wrong: ", t.get(200), 2);

	if (t.getArraySize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("wrong arraysize: ", t.getArraySize(), 2);
	if (t.getTotalSize() != HybridTable::INITIAL_ARRAY_SIZE + 2)
		errorOut_("wrong totalsize: ", t.getTotalSize(), 2);

	}
	passOut_();
}

// get/set list part: various insert positions
void HybridTableTester::testf() {
	funcname_ = "HybridTableTester::testf";
	{

	HybridTable t;
	t.set(300,3);

	// second item before first
	t.set(100,1);
	if (t.get(100) != 1) errorOut_("get100 wrong: ", t.get(100), 1);
	if (t.get(300) != 3) errorOut_("get300 wrong: ", t.get(300), 1);
	if (t.getTotalSize() != HybridTable::INITIAL_ARRAY_SIZE + 2)
		errorOut_("after step1 wrong totalsize: ", t.getTotalSize(), 1);

	// tail
	t.set(500,5);
	if (t.get(500) != 5) errorOut_("get500 wrong: ", t.get(500), 1);
	if (t.getTotalSize() != HybridTable::INITIAL_ARRAY_SIZE + 3)
		errorOut_("after step2 wrong totalsize: ", t.getTotalSize(), 1);

	// 2nd
	t.set(200,2);
	if (t.get(200) != 2) errorOut_("get200 wrong: ", t.get(200), 1);
	if (t.getTotalSize() != HybridTable::INITIAL_ARRAY_SIZE + 4)
		errorOut_("after step3 wrong totalsize: ", t.getTotalSize(), 1);

	// 2nd from last
	t.set(400,4);
	if (t.get(400) != 4) errorOut_("get400 wrong: ", t.get(400), 2);
	if (t.getTotalSize() != HybridTable::INITIAL_ARRAY_SIZE + 5)
		errorOut_("after step4 wrong totalsize: ", t.getTotalSize(), 2);

	// before 1st
	t.set(50,-1);
	if (t.get(50) != -1) errorOut_("get50 wrong: ", t.get(50), 2);
	// check all again
	if (t.get(100) != 1) errorOut_("get100 wrong: ", t.get(100), 2);
	if (t.get(200) != 2) errorOut_("get200 wrong: ", t.get(200), 2);
	if (t.get(300) != 3) errorOut_("get300 wrong: ", t.get(300), 2);
	if (t.get(400) != 4) errorOut_("get400 wrong: ", t.get(400), 2);
	if (t.get(500) != 5) errorOut_("get500 wrong: ", t.get(500), 2);
	if (t.getArraySize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("after step5 wrong arraysize: ", t.getArraySize(), 2);
	if (t.getTotalSize() != HybridTable::INITIAL_ARRAY_SIZE + 6)
		errorOut_("after step5 wrong totalsize: ", t.getTotalSize(), 2);

	}
	passOut_();
}

// get/set list part: already exists; -ve index
void HybridTableTester::testg() {
	funcname_ = "HybridTableTester::testg";
	{

	HybridTable t;
	t.set(100,100);
	t.set(300,300);
	t.set(200,200);
	//overwrite
	t.set(200,20);
	t.set(300,30);
	t.set(100,10);

	if (t.get(100) != 10) errorOut_("get100 wrong: ", t.get(100), 1);
	if (t.get(200) != 20) errorOut_("get200 wrong: ", t.get(200), 1);
	if (t.get(300) != 30) errorOut_("get300 wrong: ", t.get(300), 1);
	if (t.getArraySize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("wrong arraysize: ", t.getArraySize(), 1);
	if (t.getTotalSize() != HybridTable::INITIAL_ARRAY_SIZE + 3)
		errorOut_("wrong totalsize: ", t.getTotalSize(), 1);

	// negatives
	t.set(-1,1997);
	t.set(-201,1999);
	t.set(-101,1998);
	if (t.get(-1) != 1997) errorOut_("get-1 wrong: ", t.get(-1), 2);
	if (t.get(-101) != 1998) errorOut_("get-101 wrong: ", t.get(-101), 2);
	if (t.get(-201) != 1999) errorOut_("get-201 wrong: ", t.get(-201), 2);
	if (t.getArraySize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("wrong arraysize: ", t.getArraySize(), 2);
	if (t.getTotalSize() != HybridTable::INITIAL_ARRAY_SIZE + 6)
		errorOut_("wrong totalsize: ", t.getTotalSize(), 2);

	}
	passOut_();
}

// get non-existent entries
void HybridTableTester::testh() {
	funcname_ = "HybridTableTester::testh";
	{

	// array part only
	HybridTable t;
	if (t.get(4) != 0) errorOut_("get4 wrong: ", t.get(4), 1);
	if (t.get(-1) != 0) errorOut_("get-1 wrong: ", t.get(-1), 1);
	if (t.get(40000) != 0) errorOut_("get40000 wrong: ", t.get(40000), 1);

	// now w list part
	t.set(10,10); t.set(20,20); t.set(30,30);
	t.set(-10,-10); t.set(-20,-20);
	if (t.get(5) != 0) errorOut_("get5 wrong: ", t.get(5), 2);
	if (t.get(15) != 0) errorOut_("get15 wrong: ", t.get(15), 2);
	if (t.get(25) != 0) errorOut_("get25 wrong: ", t.get(25), 2);
	if (t.get(35) != 0) errorOut_("get35 wrong: ", t.get(35), 2);
	if (t.get(-5) != 0) errorOut_("get-5 wrong: ", t.get(-5), 2);
	if (t.get(-15) != 0) errorOut_("get-15 wrong: ", t.get(-15), 2);
	if (t.get(-25) != 0) errorOut_("get-25 wrong: ", t.get(-25), 2);

	}
	passOut_();
}

// toString from ctor
void HybridTableTester::testi() {
	funcname_ = "HybridTableTester::testi";
	{

	HybridTable t;
	if (t.toString() != "0 : 0\n1 : 0\n2 : 0\n3 : 0")
		errorOut_("def HT printed as:\n", t.toString(), 1);

	const int a[10] = {3,1,4,1,5,9,2,6,5,4};
	HybridTable u(a, 10);
	if (u.toString() != "0 : 3\n1 : 1\n2 : 4\n3 : 1\n4 : 5\n5 : 9\n6 : 2\n7 : 6\n8 : 5\n9 : 4")
		errorOut_("param HT printed as:\n", u.toString(), 2);

	}
	passOut_();
}

// tostring array part only
void HybridTableTester::testj() {
	funcname_ = "HybridTableTester::testj";
	{

	HybridTable t;
	t.set(0,3); t.set(2,1); t.set(3,0); t.set(1,2);
	if (t.toString() != "0 : 3\n1 : 2\n2 : 1\n3 : 0")
		errorOut_("step1 printed as:\n", t.toString(), 1);

	// overwrite
	t.set(2,-1); t.set(1,-2); t.set(3,0); t.set(0,-3);
	if (t.toString() != "0 : -3\n1 : -2\n2 : -1\n3 : 0")
		errorOut_("step2 printed as:\n", t.toString(), 2);

	}
	passOut_();
}

// toString array and list part (param ctor)
void HybridTableTester::testk() {
	funcname_ = "HybridTableTester::testk";
	{

	const int a[] = {99,88,77,66,55};
	HybridTable t(a, 5);
	t.set(9,44);
	if (t.toString() != "0 : 99\n1 : 88\n2 : 77\n3 : 66\n4 : 55\n---\n9 : 44")
		errorOut_("after set9 printed as:\n", t.toString(), 1);

	t.set(100,1);
	if (t.toString() != "0 : 99\n1 : 88\n2 : 77\n3 : 66\n4 : 55\n---\n9 : 44 --> 100 : 1")
		errorOut_("after set100 printed as:\n", t.toString(), 1);

	// overwite
	t.set(9,404);
	if (t.toString() != "0 : 99\n1 : 88\n2 : 77\n3 : 66\n4 : 55\n---\n9 : 404 --> 100 : 1")
		errorOut_("after set9 printed as:\n", t.toString(), 2);

	// negative
	t.set(-1,-123);
	if (t.toString() != "0 : 99\n1 : 88\n2 : 77\n3 : 66\n4 : 55\n---\n-1 : -123 --> 9 : 404 --> 100 : 1")
		errorOut_("after set-1 printed as:\n", t.toString(), 2);

	}
	passOut_();
}

// toString list part only: check various insert pos, same as case f
void HybridTableTester::testl() {
	funcname_ = "HybridTableTester::testl";
	{

	HybridTable t;
	// first
	t.set(300,3);
	if (t.toString() != "0 : 0\n1 : 0\n2 : 0\n3 : 0\n---\n300 : 3")
		errorOut_("after 300 printed as:\n", t.toString(), 1);

	// second b4 first
	t.set(100,1);
	if (t.toString() != "0 : 0\n1 : 0\n2 : 0\n3 : 0\n---\n100 : 1 --> 300 : 3")
		errorOut_("after 100 printed as:\n", t.toString(), 1);

	// tail
	t.set(500,5);
	if (t.toString() != "0 : 0\n1 : 0\n2 : 0\n3 : 0\n---\n100 : 1 --> 300 : 3 --> 500 : 5")
		errorOut_("after 500 printed as:\n", t.toString(), 1);

	// 2nd
	t.set(200,2);
	if (t.toString() != "0 : 0\n1 : 0\n2 : 0\n3 : 0\n---\n100 : 1 --> 200 : 2 --> 300 : 3 --> 500 : 5")
		errorOut_("after 200 printed as:\n", t.toString(), 2);

	// 2nd from last
	t.set(400,4);
	if (t.toString() != "0 : 0\n1 : 0\n2 : 0\n3 : 0\n---\n100 : 1 --> 200 : 2 --> 300 : 3 --> 400 : 4 --> 500 : 5")
		errorOut_("after 400 printed as:\n", t.toString(), 2);

	// before 1st
	t.set(50,-1);
	if (t.toString() != "0 : 0\n1 : 0\n2 : 0\n3 : 0\n---\n50 : -1 --> 100 : 1 --> 200 : 2 --> 300 : 3 --> 400 : 4 --> 500 : 5")
		errorOut_("after 50 printed as:\n", t.toString(), 2);

	}
	passOut_();
}

// array/list part interleaved mixed get/set + toString
void HybridTableTester::testm() {
	funcname_ = "HybridTableTester::testm";
	{

	HybridTable t;
	t.set(2,1);
	if (t.toString() != "0 : 0\n1 : 0\n2 : 1\n3 : 0")
		errorOut_("after step0 printed as:\n", t.toString(), 1);
	t.set(5,15);
	if (t.toString() != "0 : 0\n1 : 0\n2 : 1\n3 : 0\n---\n5 : 15")
		errorOut_("after step1 printed as:\n", t.toString(), 1);
	t.set(10,4);
	if (t.toString() != "0 : 0\n1 : 0\n2 : 1\n3 : 0\n---\n5 : 15 --> 10 : 4")
		errorOut_("after step2 printed as:\n", t.toString(), 1);
	t.set(2,99);
	if (t.toString() != "0 : 0\n1 : 0\n2 : 99\n3 : 0\n---\n5 : 15 --> 10 : 4")
		errorOut_("after step3 printed as:\n", t.toString(), 1);
	t.set(0,10);
	if (t.toString() != "0 : 10\n1 : 0\n2 : 99\n3 : 0\n---\n5 : 15 --> 10 : 4")
		errorOut_("after step4 printed as:\n", t.toString(), 1);
	t.set(-357,2);
	if (t.toString() != "0 : 10\n1 : 0\n2 : 99\n3 : 0\n---\n-357 : 2 --> 5 : 15 --> 10 : 4")
		errorOut_("after step5 printed as:\n", t.toString(), 1);
	t.set(5,16);
	if (t.toString() != "0 : 10\n1 : 0\n2 : 99\n3 : 0\n---\n-357 : 2 --> 5 : 16 --> 10 : 4")
		errorOut_("after step6 printed as:\n", t.toString(), 1);
	t.set(2046,11);
	if (t.toString() != "0 : 10\n1 : 0\n2 : 99\n3 : 0\n---\n-357 : 2 --> 5 : 16 --> 10 : 4 --> 2046 : 11")
		errorOut_("after step7 printed as:\n", t.toString(), 1);

	if (t.get(0) != 10) errorOut_("get0 wrong: ", t.get(0), 2);
	if (t.get(1) != 0) errorOut_("get1 wrong: ", t.get(1), 2);
	if (t.get(2) != 99) errorOut_("get2 wrong: ", t.get(2), 2);
	if (t.get(-358) != 0) errorOut_("get-358 wrong: ", t.get(-358), 2);
	if (t.get(-357) != 2) errorOut_("get-357 wrong: ", t.get(-357), 2);
	if (t.get(4) != 0) errorOut_("get4 wrong: ", t.get(4), 2);
	if (t.get(5) != 16) errorOut_("get5 wrong: ", t.get(5), 2);
	if (t.get(10) != 4) errorOut_("get10 wrong: ", t.get(10), 2);
	if (t.get(100) != 0) errorOut_("get100 wrong: ", t.get(100), 2);
	if (t.get(2046) != 11) errorOut_("get2046 wrong: ", t.get(2046), 2);
	if (t.get(2047) != 0) errorOut_("get2047 wrong: ", t.get(2047), 2);

	}
	passOut_();
}

// basic copy con
void HybridTableTester::testn() {
	funcname_ = "HybridTableTester::testn";
	{

	// array part only
	HybridTable t;
	t.set(1,10); t.set(3,30);
	string s1 = t.toString();

	HybridTable t1(t);
	for(int i=0; i<=4; i++) // include out of range index 4
		if (t1.get(i) != t.get(i))
			errorOut_("copy get" + std::to_string(i) + " wrong: ", t1.get(i), 1);

	if (t1.toString() != s1)
		errorOut_("copy printed differently:\n", t1.toString(), 1);
	if (t1.getArraySize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("copy wrong arraysize: ", t1.getArraySize(), 1);
	if (t1.getTotalSize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("copy wrong totalsize: ", t1.getTotalSize(), 1);

	// with list part
	t.set(8,80); t.set(15,150);
	string s2 = t.toString();

	HybridTable t2(t);
	for(int i=0; i<=16; i++) // include out of range indices
		if (t2.get(i) != t.get(i))
			errorOut_("copy get" + std::to_string(i) + " wrong: ", t2.get(i), 2);

	if (t2.toString() != s2)
		errorOut_("copy printed differently:\n", t2.toString(), 2);
	if (t2.getArraySize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("copy wrong arraysize: ", t2.getArraySize(), 2);
	if (t2.getTotalSize() != HybridTable::INITIAL_ARRAY_SIZE + 2)
		errorOut_("copy wrong totalsize: ", t2.getTotalSize(), 2);

	}
	passOut_();
}

// copy con: bigger array, longer list, sticky, damaged org
void HybridTableTester::testo() {
	funcname_ = "HybridTableTester::testo";
	{

	const int a[] = {0,10,20,30,40,50,60,70};
	HybridTable t(a,8);
	t.set(-2,-20); t.set(9,90); t.set(40,400); t.set(100,1000);
	string s1 = t.toString();

	HybridTable t2(t);
	for(int i=0; i<=9; i++)
		if (t2.get(i) != t.get(i))
			errorOut_("copy get" + std::to_string(i) + " wrong: ", t2.get(i), 1);

	if (t2.get(-2) != -20) errorOut_("copy get-2 wrong: ", t2.get(-2), 1);
	if (t2.get(9) != 90) errorOut_("copy get9 wrong: ", t2.get(9), 1);
	if (t2.get(40) != 400) errorOut_("copy get40 wrong: ", t2.get(40), 1);
	if (t2.get(100) != 1000) errorOut_("copy get100 wrong: ", t2.get(100), 1);

	if (t2.getArraySize() != 8)
		errorOut_("copy wrong arraysize: ", t2.getArraySize(), 1);
	if (t2.getTotalSize() != 12)
		errorOut_("copy wrong totalsize: ", t2.getTotalSize(), 1);
	if (t2.toString() != s1)
		errorOut_("copy printed differently:\n", t2.toString(), 1);

	// damaged org?
	if (t.get(1) != 10) errorOut_("org get1 wrong: ", t.get(1), 2);
	if (t.get(5) != 50) errorOut_("org get5 wrong: ", t.get(5), 2);
	if (t.get(9) != 90) errorOut_("org get9 wrong: ", t.get(9), 2);
	if (t.get(40) != 400) errorOut_("org get15 wrong: ", t.get(40), 2);
	if (t.getArraySize() != 8)
		errorOut_("org wrong arraysize: ", t.getArraySize(), 2);
	if (t.getTotalSize() != 12)
		errorOut_("org wrong totalsize: ", t.getTotalSize(), 2);
	if (t.toString() != s1)
		errorOut_("org printed differently:\n", t.toString(), 2);

	// sticky?
	t.set(2,-20); t.set(13,-130); t.set(40,-40); // one each: array, not in list, in list
	t2.set(1,-10); t2.set(9,-90); t2.set(200,-2000);
	if (t2.get(2) != 20)
		errorOut_("sticky copy con: old affected new", 2);
	if (t2.get(13) != 0)
		errorOut_("sticky copy con: old affected new", 2);
	if (t2.get(40) != 400)
		errorOut_("sticky copy con: old affected new", 2);
	if (t.get(1) != 10)
		errorOut_("sticky copy con: new affected old", 2);
	if (t.get(9) != 90)
		errorOut_("sticky copy con: new affected old", 2);
	if (t.get(200) != 0)
		errorOut_("sticky copy con: new affected old", 2);

	}
	passOut_();
}

// basic copy asg
void HybridTableTester::testp() {
	funcname_ = "HybridTableTester::testp";
	{

	// array part only
	HybridTable t;
	t.set(1,10); t.set(3,30);
	string s1 = t.toString();

	HybridTable t1;
	t1 = t;
	for(int i = 0; i <= 4; i++) // include out of range index 4
		if (t1.get(i) != t.get(i))
			errorOut_("copy get" + std::to_string(i) + " wrong: ", t1.get(i), 1);

	if (t1.toString() != s1)
		errorOut_("copy printed differently:\n", t1.toString(), 1);
	if (t1.getArraySize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("copy wrong arraysize: ", t1.getArraySize(), 1);
	if (t1.getTotalSize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("copy wrong totalsize: ", t1.getTotalSize(), 1);

	// with list part
	t.set(8,80); t.set(15,150);
	string s2 = t.toString();

	HybridTable t2;
	t2 = t;
	for(int i = 0; i <= 16; i++) // include out of range indices
		if (t2.get(i) != t.get(i))
			errorOut_("copy get" + std::to_string(i) + " wrong: ", t2.get(i), 2);

	if (t2.toString() != s2)
		errorOut_("copy printed differently:\n", t2.toString(), 2);
	if (t2.getArraySize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("copy wrong arraysize: ", t2.getArraySize(), 2);
	if (t2.getTotalSize() != HybridTable::INITIAL_ARRAY_SIZE + 2)
		errorOut_("copy wrong totalsize: ", t2.getTotalSize(), 2);

	}
	passOut_();
}

// copy asg: bigger array, longer list, sticky, damaged org
void HybridTableTester::testq() {
	funcname_ = "HybridTableTester::testq";
	{

	const int a[] = {0,10,20,30,40,50,60,70};
	HybridTable t(a,8);
	t.set(-2,-20); t.set(9,90); t.set(40,400); t.set(100,1000);
	string s1 = t.toString();

	HybridTable t2;
	t2 = t;
	for(int i = 0; i <= 9; i++)
		if (t2.get(i) != t.get(i))
			errorOut_("copy get" + std::to_string(i) + " wrong: ", t2.get(i), 1);

	if (t2.get(-2) != -20) errorOut_("copy get-2 wrong: ", t2.get(-2), 1);
	if (t2.get(9) != 90) errorOut_("copy get9 wrong: ", t2.get(9), 1);
	if (t2.get(40) != 400) errorOut_("copy get40 wrong: ", t2.get(40), 1);
	if (t2.get(100) != 1000) errorOut_("copy get100 wrong: ", t2.get(100), 1);

	if (t2.getArraySize() != 8)
		errorOut_("copy wrong arraysize: ", t2.getArraySize(), 1);
	if (t2.getTotalSize() != 12)
		errorOut_("copy wrong totalsize: ", t2.getTotalSize(), 1);
	if (t2.toString() != s1)
		errorOut_("copy printed differently:\n", t2.toString(), 1);

	// damaged org?
	if (t.get(1) != 10) errorOut_("org get1 wrong: ", t.get(1), 2);
	if (t.get(5) != 50) errorOut_("org get5 wrong: ", t.get(5), 2);
	if (t.get(9) != 90) errorOut_("org get9 wrong: ", t.get(9), 2);
	if (t.get(40) != 400) errorOut_("org get15 wrong: ", t.get(40), 2);
	if (t.getArraySize() != 8)
		errorOut_("org wrong arraysize: ", t.getArraySize(), 2);
	if (t.getTotalSize() != 12)
		errorOut_("org wrong totalsize: ", t.getTotalSize(), 2);
	if (t.toString() != s1)
		errorOut_("org printed differently:\n", t.toString(), 2);

	// sticky?
	t.set(2,-20); t.set(13,-130); t.set(40,-40);
	t2.set(1,-10); t2.set(9,-90); t2.set(200,-2000);
	if (t2.get(2) != 20)
		errorOut_("sticky copy asg: old affected new", 2);
	if (t2.get(13) != 0)
		errorOut_("sticky copy asg: old affected new", 2);
	if (t2.get(40) != 400)
		errorOut_("sticky copy asg: old affected new", 2);
	if (t.get(1) != 10)
		errorOut_("sticky copy asg: new affected old", 2);
	if (t.get(9) != 90)
		errorOut_("sticky copy asg: new affected old", 2);
	if (t.get(200) != 0)
		errorOut_("sticky copy asg: new affected old", 2);

	}
	passOut_();
}

// copy asg: old one overwritten?
void HybridTableTester::testr() {
	funcname_ = "HybridTableTester::testr";
	{

	// old bigger array, new empty list
	int a[10] = {0};
	HybridTable t1(a,10);
	t1.set(16,16); t1.set(17,17);
	string s1 = t1.toString();
	HybridTable t2;
	t2.set(1,1);
	t2 = t1;
	if (t2.getArraySize() != 10)
		errorOut_("copy wrong arraysize: ", t2.getArraySize(), 1);
	if (t2.getTotalSize() != 12)
		errorOut_("copy wrong totalsize: ", t2.getTotalSize(), 1);
	if (t2.toString() != s1)
		errorOut_("copy printed differently:\n", t2.toString(), 1);

	// new bigger array, old empty list
	HybridTable u1;
	u1.set(1,1);
	string s2 = u1.toString();
	HybridTable u2(a,10);
	u2.set(16,16); u2.set(17,17);
	u2 = u1;
	if (u2.getArraySize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("copy wrong arraysize: ", u2.getArraySize(), 2);
	if (u2.getTotalSize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("copy wrong totalsize: ", u2.getTotalSize(), 2);
	if (u2.toString() != s2)
		errorOut_("copy printed differently:\n", u2.toString(), 2);

	}
	passOut_();
}

// copy asg self-asg
void HybridTableTester::tests() {
	funcname_ = "HybridTableTester::tests";
	{

	HybridTable t;
	// array part
	t.set(1,10);
	t = t;
	t.set(3,30);
	if (t.get(1) != 10) errorOut_("get1 wrong: ", t.get(1), 1);
	if (t.get(2) != 0) errorOut_("get2 wrong: ", t.get(2), 1);
	if (t.get(3) != 30) errorOut_("get3 wrong: ", t.get(3), 1);
	if (t.get(100) != 0) errorOut_("get100 wrong: ", t.get(100), 1);
	if (t.getArraySize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("wrong arraysize: ", t.getArraySize(), 1);
	if (t.getTotalSize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("wrong totalsize: ", t.getTotalSize(), 1);

	// list part
	t.set(10,20); t.set(100,30); t.set(1000,40);
	t = t;
	t.set(10000,50);
	if (t.get(1) != 10) errorOut_("get1 wrong: ", t.get(1), 2);
	if (t.get(2) != 0) errorOut_("get2 wrong: ", t.get(2), 2);
	if (t.get(3) != 30) errorOut_("get3 wrong: ", t.get(3), 2);
	if (t.get(10) != 20) errorOut_("get10 wrong: ", t.get(10), 2);
	if (t.get(20) != 0) errorOut_("get20 wrong: ", t.get(20), 2);
	if (t.get(100) != 30) errorOut_("get100 wrong: ", t.get(100), 2);
	if (t.get(1000) != 40) errorOut_("get1000 wrong: ", t.get(1000), 2);
	if (t.get(10000) != 50) errorOut_("get10000 wrong: ", t.get(10000), 2);
	if (t.getArraySize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("wrong arraysize: ", t.getArraySize(), 2);
	if (t.getTotalSize() != HybridTable::INITIAL_ARRAY_SIZE + 4)
		errorOut_("wrong totalsize: ", t.getTotalSize(), 2);

	}
	passOut_();
}

// resize: basic
void HybridTableTester::testt() {
	funcname_ = "HybridTableTester::testt";
	{

	HybridTable t;
	// just before first resize
	t.set(1,1); t.set(2,2);	t.set(3,3); t.set(4,4);
	if (t.getArraySize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("b4 resize wrong arraysize: ", t.getArraySize(), 1);
	if (t.getTotalSize() != HybridTable::INITIAL_ARRAY_SIZE + 1)
		errorOut_("b4 resize wrong arraysize: ", t.getTotalSize(), 1);

	// first resize
	t.set(5,5);
	if (t.getArraySize() != 2*HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("1st resize wrong arraysize: ", t.getArraySize(), 1);
	if (t.getTotalSize() != 2*HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("1st resize wrong arraysize: ", t.getTotalSize(), 1);

	// just before second resize
	t.set(7,7); t.set(8,8); t.set(9,9); t.set(10,10);
	if (t.getArraySize() != 2*HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("b4 2nd resize wrong arraysize: ", t.getArraySize(), 2);
	if (t.getTotalSize() != 2*HybridTable::INITIAL_ARRAY_SIZE + 3)
		errorOut_("b4 2nd resize wrong arraysize: ", t.getTotalSize(), 2);

	// second resize
	t.set(11,11);
	if (t.getArraySize() != 4*HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("2nd resize wrong arraysize: ", t.getArraySize(), 2);
	if (t.getTotalSize() != 4*HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("2nd resize wrong arraysize: ", t.getTotalSize(), 2);

	}
	passOut_();
}

// resize check get/tostring
void HybridTableTester::testu() {
	funcname_ = "HybridTableTester::testu";
	{

	HybridTable t;
	// first resize
	for(int i = 1; i <= 5; i++) t.set(i,i);
	for(int i = 0; i <= 5; i++)
		if (t.get(i) != i)
			errorOut_("1st resize wrong get: ", t.get(i), 1);
	if (t.toString() != "0 : 0\n1 : 1\n2 : 2\n3 : 3\n4 : 4\n5 : 5\n6 : 0\n7 : 0")
		errorOut_("after resize [0..7] wrong tostring:\n", t.toString(), 1);

	// just before second resize, list part
	for(int i = 6; i <= 10; i++) t.set(i,i);
	for(int i = 0; i <= 10; i++)
		if (t.get(i) != i)
			errorOut_("b4 2nd resize wrong get: ", t.get(i), 1);
	if (t.toString() != "0 : 0\n1 : 1\n2 : 2\n3 : 3\n4 : 4\n5 : 5\n6 : 6\n7 : 7\n---\n8 : 8 --> 9 : 9 --> 10 : 10")
		errorOut_("after adding 8-10 wrong tostring:\n", t.toString(), 1);

	// second resize
	t.set(11,11);
	for(int i = 0; i <= 11; i++)
		if (t.get(i) != i)
			errorOut_("2nd resize wrong get: ", t.get(i), 2);
	if (t.toString() != "0 : 0\n1 : 1\n2 : 2\n3 : 3\n4 : 4\n5 : 5\n6 : 6\n7 : 7\n8 : 8\n9 : 9\n10 : 10\n11 : 11\n12 : 0\n13 : 0\n14 : 0\n15 : 0")
		errorOut_("after adding 11 wrong tostring:\n", t.toString(), 2);

	// w some left in list part after resize; larger array
	const int a[] = {9,8,7,6,5,4,3,2,1};
	HybridTable u(a, 9);
	for(int i = 17; i >= 13; i--) u.set(i,i);
	for(int i = 17; i >= 13; i--)
		if (u.get(i) != i)
			errorOut_("resize wrong get: ", u.get(i), 2);
	if (u.toString() != "0 : 9\n1 : 8\n2 : 7\n3 : 6\n4 : 5\n5 : 4\n6 : 3\n7 : 2\n8 : 1\n9 : 0\n10 : 0\n11 : 0\n12 : 0\n13 : 13\n14 : 14\n15 : 15\n---\n16 : 16 --> 17 : 17")
		errorOut_("after resize [0..15] wrong tostring:\n", u.toString(), 2);

	}
	passOut_();
}

// resize precise boundaries 1
void HybridTableTester::testv() {
	funcname_ = "HybridTableTester::testv";
	{

	// skip past [0..7] and jump directly to [0..15]
	HybridTable t;
	t.set(1,1); t.set(2,2);	t.set(3,3);
	t.set(4,4);
	t.set(8,8);
	if (t.getArraySize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("after set8 wrong size: ", t.getArraySize(), 1);

	for(int i = 9; i <= 13; i++) t.set(i,i);
	if (t.getArraySize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("after set13 wrong size: ", t.getArraySize(), 1);

	t.set(14,14);
	if (t.getArraySize() != 4*HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("after set14 wrong size: ", t.getArraySize(), 1);

	// skip past [0..7] but come back to it later
	HybridTable u;
	u.set(1,1); u.set(2,2);	u.set(3,3);
	u.set(7,7);
	for(int i = 8; i <= 12; i++) u.set(i,i);
	if (u.getArraySize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("after set12 wrong size: ", u.getArraySize(), 1);
	u.set(6,6);
	if (u.getArraySize() != 2*HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("after set6 wrong size: ", u.getArraySize(), 1);
	// (this one might wrongly trigger resize to 16 if resize call set which call resize?)

	// jump past many empty ones
	HybridTable v;
	for(int i = 69; i < 128; i++) v.set(i,i);
	for(int i = 128; i < 256; i++) v.set(i,i); // 4+59+128 out of 256
	if (v.getArraySize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("after set255 wrong size: ", v.getArraySize(), 2);
	v.set(68,68);
	if (v.getArraySize() != 256)
		errorOut_("after set68 wrong size: ", v.getArraySize(), 2);

	// many (separated) ranges, choose biggest one
	HybridTable w;
	// all these just one short (skipping 8, to be added at the end)
	for(int i = 9; i < 16; i++) w.set(i,i); // 4+7 out of 16
	for(int i = 28; i < 64; i++) w.set(i,i); // 4+7+36 out of 64
	for(int i = 112; i < 256; i++) w.set(i,i); // 4+7+36+144 out of 256
	// this one still one short even after 8
	for(int i = 448; i < 1023; i++) w.set(i,i); // 4+7+36+144+576 out of 1024
	if (w.getArraySize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("after set1022 wrong size: ", w.getArraySize(), 2);
	w.set(8,8);
	if (w.getArraySize() != 256)
		errorOut_("after set8 wrong size: ", w.getArraySize(), 2);

	}
	passOut_();
}

// resize precise boundaries 2
void HybridTableTester::testw() {
	funcname_ = "HybridTableTester::testw";
	{

	const int a[] = {0,1,2,3,4,5,6,7,8,9,10,11};

	// negatives
	HybridTable t;
	for(int i = -4; i < 0; i++) t.set(i,i);
	if (t.getArraySize() != HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("t wrong size: ", t.getArraySize(), 1);

	// get/set existing ones should not trigger
	HybridTable u(a, 8);
	for(int i = 0; i < 11; i++) u.set(i, i);
	for(int i = 0; i < 11; i++) u.set(i, u.get(i));
	if (u.getArraySize() != 8)
		errorOut_("u wrong size: ", u.getArraySize(), 1);

	// start w non-power-2 param ctor
	HybridTable v(a,10);
	v.set(16,16);
	if (v.getArraySize() != 10)
		errorOut_("v after set16 wrong size: ", v.getArraySize(), 2);
	for(int i = 8; i <= 22; i++) v.set(i,i);
	if (v.getArraySize() != 16)
		errorOut_("v after set22 wrong size: ", v.getArraySize(), 2);

	// due to param ctor triggered immediately
	HybridTable w(a,12);
	w.set(-1,-1);
	if (w.getArraySize() != 16)
		errorOut_("w wrong size: ", w.getArraySize(), 2);

	// param ctor but not triggered
	HybridTable w2(a,11);
	w2.set(-1,-1);
	if (w2.getArraySize() != 11)
		errorOut_("w2 wrong size: ", w2.getArraySize(), 2);

	}
	passOut_();
}

// get/set v large indices; may fail if resize not careful w overflow
void HybridTableTester::testx() {
	funcname_ = "HybridTableTester::testx";
	{

	HybridTable t;
	t.set(INT_MAX, INT_MIN);
	t.set(INT_MIN, INT_MAX);
	t.set(4,4); t.set(5,5);
	if (t.get(INT_MAX) != INT_MIN) errorOut_("largest int index incorrect", 1);
	if (t.get(INT_MIN) != INT_MAX) errorOut_("smallest int index incorrect", 1);
	if (t.getArraySize() != 2*HybridTable::INITIAL_ARRAY_SIZE)
		errorOut_("wrong arraysize: ", t.getArraySize(), 2);
	if (t.getTotalSize() != 2*HybridTable::INITIAL_ARRAY_SIZE + 2)
		errorOut_("wrong totalsize: ", t.getTotalSize(), 2);

	}
	passOut_();
}

// resize w/ copy
void HybridTableTester::testy() {
	funcname_ = "HybridTableTester::testy";
	{

	// copy after resize
	// 0 1 2 3 5 6 8 9 10 11 12 13 30 31
	HybridTable t;
	for(int i = 8; i < 14; i++) t.set(i,i);
	t.set(30,30); t.set(31,31); t.set(5,5); t.set(6,6);
	HybridTable u;
	u = t;
	for(int i = 0; i <= 32; i++)
		if (t.get(i) != u.get(i))
			errorOut_("u wrong val at index ", i, 1);
	if (u.getArraySize() != 16)
		errorOut_("u wrong arraysize: ", u.getArraySize(), 1);
	if (u.getTotalSize() != 16+2)
		errorOut_("u wrong totalsize: ", u.getTotalSize(), 1);

	// resize again after copy
	for(int i = 16; i < 22; i++) u.set(i,i);
	HybridTable v = u;
	for(int i = 0; i <= 32; i++)
		if (v.get(i) != u.get(i))
			errorOut_("v wrong val at index ", i, 1);
	if (v.getArraySize() != 32)
		errorOut_("v wrong arraysize: ", v.getArraySize(), 1);
	if (v.getTotalSize() != 32)
		errorOut_("v wrong totalsize: ", v.getTotalSize(), 1);

	// cascading resize
	HybridTable w;
	for(int i = 8; i <= 12; i++) w.set(i,i);
	w.set(4,4); w.set(5,5);
	// should only resize to 8 here
	if (w.getArraySize() != 8)
		errorOut_("after set5 wrong arraysize: ", w.getArraySize(), 2);
	// should still be 8 even though 16 now qualifies as 75% due to expanded array
	w.set(5,-5);
	if (w.getArraySize() != 8)
		errorOut_("after set5 again wrong arraysize: ", w.getArraySize(), 2);
	// still 8 here
	HybridTable w2(w);
	if (w2.getArraySize() != 8)
		errorOut_("after copy wrong arraysize: ", w2.getArraySize(), 2);

	// only here becomes 16
	w.set(1000,1000);
	if (w.getArraySize() != 16)
		errorOut_("after set1000 wrong arraysize: ", w.getArraySize(), 2);

	}
	passOut_();
}

// reserved for new test cases
void HybridTableTester::testz() {
	funcname_ = "HybridTableTester::testz";
	{


	}
	passOut_();
}

void HybridTableTester::errorOut_(const string& errMsg, unsigned int errBit) {

	cerr << funcname_ << ":" << " fail" << errBit << ": ";
	cerr << errMsg << endl;
	error_ |= (1<<errBit);
	cerr << std::flush;
}

void HybridTableTester::errorOut_(const string& errMsg, const string& errResult, unsigned int errBit) {

	cerr << funcname_ << ":" << " fail" << errBit << ": ";
	cerr << errMsg << errResult << endl;
	error_ |= (1<<errBit);
	cerr << std::flush;
}

void HybridTableTester::errorOut_(const string& errMsg, int errResult, unsigned int errBit) {

	cerr << funcname_ << ":" << " fail" << errBit << ": ";
	cerr << errMsg << std::to_string(errResult) << endl;
	error_ |= (1<<errBit);
	cerr << std::flush;
}

void HybridTableTester::passOut_() {

	if (!error_) {
		cerr << funcname_ << ":" << " pass" << endl;
	}
	cerr << std::flush;
}

