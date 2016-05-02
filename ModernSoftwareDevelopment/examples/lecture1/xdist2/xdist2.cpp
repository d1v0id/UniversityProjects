// xdist2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

class Distance
{
public:
	class InchesException
	{
	public:
		string origin;
		float iValue;
		InchesException(string or, float in)
		{
			origin = or;
			iValue = in;
		}
	};

	Distance() : feet(0), inches(0.0)
	{
	}

	Distance(int ft, float in)
	{
		if (in >= 12.0) {
			throw InchesException("Constructor with two parameters: ", in);
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
			throw InchesException("getDist() function: ", inches);
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
	catch (Distance::InchesException ix) {
		cout << endl << "Initialization error: " << ix.origin << endl;
		cout << "Incorrect inches value " << ix.iValue << endl;
	}

	system("pause");

	return 0;
}

