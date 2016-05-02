// tmplstack2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>

using namespace std;

template <class T, int size>
class Stack
{
public:
	Stack(int size = 10) : st(new T[size]), top(-1)
	{
	}

	void push(T var)
	{
		st[++top] = var;
	}

	T pop()
	{
		return st[top--];
	}

	~Stack()
	{
		delete[] st;
	}

private:
	T* st;
	int top;
};

int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Stack<int, 5> s1;
	s1.push(1);
	s1.push(2);
	s1.push(3);
	s1.push(4);

	cout << s1.pop() << endl;
	cout << s1.pop() << endl;
	cout << s1.pop() << endl;
	cout << s1.pop() << endl;

	Stack<float, 5> s2;
	s2.push(1.1);
	s2.push(2.2);
	s2.push(3.3);
	s2.push(4.4);

	cout << s2.pop() << endl;
	cout << s2.pop() << endl;
	cout << s2.pop() << endl;
	cout << s2.pop() << endl;

	system("pause");

	return 0;
}

