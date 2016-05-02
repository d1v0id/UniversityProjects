// xcpt1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <windows.h>

using namespace std;

class TaleTellingClass
{
public:
	TaleTellingClass()
	{
		cout << "TaleTellingClass: constructor" << endl; 
	}
	~TaleTellingClass()
	{
		cout << "TaleTellingClass: ... destructor." << endl; 
	}
};

void function1(void)
{
	ifstream ifs("\\INVALID\\FILE\\NAME");
	if (!ifs) {
		cout << "Throw exception..." << endl;
		// Выбросить 'const char*'
		throw "Open file error...";
	}
	
	// В противном случае, файл открыт успешно
}

void function2(void)
{
	//
	// Создать локальный объект, чтобы проверить вызов 
	// деструктора при разматывании стека
	// .
	TaleTellingClass tellme;

	//
	// Вызвать функцию, выбрасывающую исключение
	//
	function1();
}


int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try {
		cout << "Into try-block..." << endl;
		function2();
		cout << "Out from try-block..." << endl;
	}
	catch (int i) {
		cout << "Execute catcher 'int' с " << i << endl;
		return -1;
	}
	catch (const char* p) {
		cout << "Execute catcher 'char*' " << "[" << p << "]" << endl;
			return -1;
	}
	catch (...) {
		cout << "Execute catcher catch_all..." << endl;
		return -1;
	}

	system("pause");

	return 0;
	// Обошлось без приключений! 
}

