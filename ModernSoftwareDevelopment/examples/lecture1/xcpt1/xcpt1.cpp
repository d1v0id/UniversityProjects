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
		// ��������� 'const char*'
		throw "Open file error...";
	}
	
	// � ��������� ������, ���� ������ �������
}

void function2(void)
{
	//
	// ������� ��������� ������, ����� ��������� ����� 
	// ����������� ��� ������������ �����
	// .
	TaleTellingClass tellme;

	//
	// ������� �������, ������������� ����������
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
		cout << "Execute catcher 'int' � " << i << endl;
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
	// �������� ��� �����������! 
}

