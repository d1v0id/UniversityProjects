// xstack1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>

using namespace std;
const int MAX = 3;

class Stack
{
public:
	class Full
	{
	};

	class Empty
	{
	};

	Stack()
	{
		top = -1;
	}

	void push(int var)
	{
		if (top >= MAX - 1) {
			throw Full();
		}
		st[++top] = var;
	}

	int pop()
	{
		if (top < 0) {
			throw Empty();
		}
		return st[top--];
	}

private:
	int st[MAX];
	int top;
};


int _tmain(int argc, _TCHAR* argv[])
{
	Stack s1;

	try {
		s1.push(11);
		s1.push(22);
		s1.push(33);
		//s1.push(44); //Стек заполнен"
		cout << "1: " << s1.pop() << endl;
		cout << "2; " << s1.pop() << endl;
		cout << "3: " << s1.pop() << endl;
		cout << "4: " << s1.pop() << endl;//Стек пуст

	}
	catch (Stack::Full) {
		cout << "Exception: Stack overflow" << endl;
	}
	catch (Stack::Empty) {
		cout << "Exception: Stack empty" << endl;
	}

	cout << "End of program" << endl;

	system("pause");

	return 0;
}

