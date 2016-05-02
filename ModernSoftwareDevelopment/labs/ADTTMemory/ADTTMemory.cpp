// ADTTMemory.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TMemory.cpp"

int _tmain(int argc, _TCHAR* argv[])
{
	TMemory<int> tMemory;
	cout << tMemory.getNumber() << endl;
	cout << tMemory.getState() << endl;

	tMemory.store(11);
	cout << tMemory.getNumber() << endl;
	cout << tMemory.getState() << endl;

	tMemory.add(5);
	cout << tMemory.getNumber() << endl;
	cout << tMemory.getState() << endl;

	cout << tMemory.restore() << endl;

	tMemory.clear();
	cout << tMemory.getNumber() << endl;
	cout << tMemory.getState() << endl;

	system("pause");

	return 0;
}

