// xdist.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>

using namespace std;

class Distance
{
public:
	class InchesException
	{
	};

	Distance()
	{
		feet = 0;
		inches = 0.0;
	}

	Distance(int ft, float in)
	{
		if (in >= 12.0) {
			throw InchesException();
		}
		feet = ft;
		inches = in;
	}

	void getDist()
	{
		cout << "Enter foot value: ";
		cin >> feet;

		cout << "Enter inches value: ";
		cin >> inches;

		if (inches >= 12.0) {
			throw InchesException();
		}
	}

	void showDist()
	{
		cout << feet << "\' - " << inches << "\'" << endl;
	}

private:
	int feet;
	float inches;
};

int _tmain(int argc, _TCHAR* argv[])
{
	try {
		Distance dist1(17, 3.5);
		Distance dist2;
		dist2.getDist();

		cout << endl << "dist1 = ";
		dist1.showDist();

		cout << endl << "dist2 = ";
		dist2.showDist();
	}
	catch (Distance::InchesException) {
		cout << endl << "Initialization error:" << endl;
		cout << "Incorrect inches value." << endl;
	}

	system("pause");

	return 0;
}

