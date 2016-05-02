// templstack5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "UTemplate.cpp"
#include <windows.h>
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Stack<> s1;
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

