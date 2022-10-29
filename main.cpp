#include <iostream>
#include "HybridTable.h"

using namespace std;

int main() {

	HybridTable t;
	t.set(0,123);
	t.set(2,456);
	cout << t.get(0) << endl;
	cout << t.get(1) << endl;
	cout << t.get(2) << endl;
	cout << t.get(3) << endl;
	cout << t.get(4) << endl;
	cout << t.toString() << endl;
	cout << t.getArraySize() << endl;
	cout << t.getTotalSize() << endl;
	cout << endl;

	t.set(6,789);
	t.set(10,42);
	t.set(-1,-42);
	cout << t.get(6) << endl;
	cout << t.get(10) << endl;
	cout << t.get(-1) << endl;
	cout << t.toString() << endl;
	cout << endl;

	int a[] = {0,1,2,3,4};
	HybridTable t2(a,5);
	cout << t2.toString() << endl;
	cout << endl;

	t2.set(8,8);
	t2.set(5,5);
	cout << t2.toString() << endl;
	cout << endl;

	HybridTable t3(t);
	cout << t3.toString() << endl;
	cout << endl;

	t3 = t2;
	cout << t3.toString() << endl;

}

