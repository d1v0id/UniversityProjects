// ADTTEditor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TEditor.h"

int _tmain(int argc, _TCHAR* argv[])
{
	TEditor editor;
	editor.setValue("11");
	cout << editor.getValue() << endl;

	editor.addNumber(12);
	cout << editor.getValue() << endl;

	editor.addZero();
	cout << editor.getValue() << endl;

	editor.changeNegativeSign();
	cout << editor.getValue() << endl;

	editor.clear();
	cout << editor.getValue() << endl;

	return 0;
}

