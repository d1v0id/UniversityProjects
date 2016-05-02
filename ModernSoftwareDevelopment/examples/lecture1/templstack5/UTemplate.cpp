#include "stdafx.h"

template <class T = int, int size = 10>
class Stack
{
public:
	Stack(int size = 10)
	{
		st = new T[size];
		top = -1;
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