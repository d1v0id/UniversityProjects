// templstack6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template<class T, int size>
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

	T pop(void)
	{
		return st[top--];
	}

	string ToString(void)
	{
		stringstream s;
		for (int i = top; i >= 0; i--) {
			s << st[i];
			
			if (i != 0) {
				s << ", ";
			}
			else {
				s << "";
			}
		}

		return s.str();
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

	cout << s1.ToString() << endl;

	cout << s1.pop() << endl;
	cout << s1.pop() << endl;
	cout << s1.pop() << endl;
	cout << s1.pop() << endl;

	Stack<float, 5> s2;
	s2.push(1.1);
	s2.push(2.2);
	s2.push(3.3);
	s2.push(4.4);

	cout << s2.ToString() << endl;

	cout << s2.pop() << endl;
	cout << s2.pop() << endl;
	cout << s2.pop() << endl;
	cout << s2.pop() << endl;
	
	system("pause");
	
	return 0;
}
