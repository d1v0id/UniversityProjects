// badalloc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	const unsigned long SIZE = 100000000000;
	char * ptr;

	try {
		ptr = new char[SIZE];
	}
	catch (bad_alloc) {
		cout << endl << "Exception bad_alloc: not enought memory." << endl;
		return(1);
	}

	delete [] ptr;

	cout << "All good." << endl;

	system("pause");

	return 0;
}

