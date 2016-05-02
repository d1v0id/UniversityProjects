// ATDTComplex.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TComplex.cpp"

int _tmain(int argc, _TCHAR* argv[])
{
	try{
		//TComplex<> tComplex();
		TComplex<> tComplex("6+i*3");
		TComplex<> tComplexCopy(tComplex);
	}
	catch (ComplexException ex) {
		cout << ex.what() << endl;
	}

	system("pause");

	return 0;
}

