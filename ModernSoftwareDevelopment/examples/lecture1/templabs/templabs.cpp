// templabs.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>

using namespace std;

template <typename T>
T abs(T n) // вычисление модулей чисел
{
	return (n < 0) ? -n : n;
}

int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int i;
	int int1 = 5;
	int int2 = -6;
	long long1 = 70000L;
	long long2 = -80000L;
	double doub1 = -9.95;
	double doub2 = -10.15;

	cout << "abs (" << int1 << ") = " << abs(int1) << endl;
	cout << "abs (" << int2 << ") = " << abs(int2) << endl;
	cout << "abs (" << long1 << ") = " << abs(long1) << endl;
	cout << "abs (" << long2 << ") = " << abs(long2) << endl;
	cout << "abs (" << doub1 << ") = " << abs(doub1) << endl;
	cout << "abs (" << doub2 << ") = " << abs(doub2) << endl;

	return 0;
}

