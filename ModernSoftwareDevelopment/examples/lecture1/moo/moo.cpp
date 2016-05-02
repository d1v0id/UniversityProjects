// moo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>

using namespace std;

void moo(void)
{
	try {
		char* n = "ошибка в функции moo()";
		throw n;
	}
	catch (char* a) {
		cout << a << endl;
		throw;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	try {
		moo();
	}
	catch (char* a) {
		cout << a << endl;
		throw;
	}

	system("pause");

	return 0;
}

