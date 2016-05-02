// tmplstack3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

template <class T, int size>
class Stack
{
public:
	Stack(int size = 10);
	void push(T var);
	T pop();
	~Stack();

private:
	T* st;
	int top;
};

template <class T, int size>
Stack<T, size>::Stack(int size)
{
	st = new T[size];
	top = -1;
}

template <class T, int size>
void Stack<T, size>::push(T var)
{
	st[++top] = var;
}

template <class T, int size>
T Stack<T, size>::pop()
{
	return st[top--];
}

template <class T, int size>
Stack<T, size>::~Stack()
{
	delete[] st;
}


int _tmain(int argc, _TCHAR* argv[])
{
	Stack<int, 5> s1;
	s1.push(1);
	s1.push(2);
	s1.push(3);

	cout << s1.pop() << endl;
	cout << s1.pop() << endl;
	cout << s1.pop() << endl;

	Stack<float, 5> s2;
	s2.push(1.1);
	s2.push(2.2);
	s2.push(3.3);

	cout << s2.pop() << endl;
	cout << s2.pop() << endl;
	cout << s2.pop() << endl;
	
	system("pause");


	return 0;
}

