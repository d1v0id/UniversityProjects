// templstack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>

using namespace std;

const int MAX = 100;

template <class Type>
class Stack
{
public:
	Stack()
	{
		top = -1;
	}

	void push(Type var)
	{
		st[++top] = var;
	}

	Type pop()
	{
		return st[top--];
	}

private:
	Type st[MAX];
	int top;
};

int _tmain(int argc, _TCHAR* argv[])
{
	/*SetConsoleCP(1251);
	SetConsoleOutputCP(1251);*/

	Stack<float> s1;
	s1.push(1111.1F);
	s1.push(2222.2F);
	s1.push(3333.3F);

	cout << "1: " << s1.pop() << endl;
	cout << "2: " << s1.pop() << endl;
	cout << "3: " << s1.pop() << endl;

	Stack<long> s2;
	s2.push(11111111L);
	s2.push(22222222L);
	s2.push(33333333L);

	cout << "1: " << s2.pop() << endl;
	cout << "2: " << s2.pop() << endl;
	cout << "3: " << s2.pop() << endl;

	system("pause");

	return 0;
}

