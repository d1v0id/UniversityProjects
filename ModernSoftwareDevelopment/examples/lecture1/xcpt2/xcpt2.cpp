// xcpt2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>

using namespace std;

class Base
{
};

class Derived : public Base
{
};

void funcA()
{
	Derived d;
	throw d;
}

void funcB()
{
	throw "Error in funcB()";
}

int _tmain(int argc, _TCHAR* argv[])
{
	try {
		funcA();
	}
	// Следующие обрабочики catch расположены неправильно:
	// обработчик 'Derived&' должен предшествовать обработчику
	// базового класса. При теперешней их последовательности
	// обработчик 'Derived&' никогда не сможет получить управление!
	catch (Base&) {
		cout << "Exception in class Base&" << endl;
	}
	catch (Derived&) {
		cout << "Exception in class Derived&" << endl;
	}

	try {
		funcB();
	}
	// Следующие обрабочики catch расположены неправильно:
	// обработчик 'const char*' должен предшествовать обработчику
	// 'void*'. При теперешней их последовательности обработчик
	// 'const char*' никогда не сможет получить управление!
	catch (void*) {
		cout << "Exception in class void*" << endl;
	}
	catch (const char*) {
		cout << "Exception in class const char*" << endl;
	}

	system("pause");

	return 0;
}

