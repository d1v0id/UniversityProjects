// ADTTProc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TProc.cpp"

int _tmain(int argc, _TCHAR* argv[])
{
	TProc<> proc;
	cout << proc.getRop() << endl;
	cout << proc.getLop_Res() << endl << endl;

	proc.ProcClear();
	cout << proc.getRop() << endl;
	cout << proc.getLop_Res() << endl << endl;

	proc.setRop(11.0);
	proc.setLop_Res(12.0);
	cout << proc.getRop() << endl;
	cout << proc.getLop_Res() << endl << endl;

	cout << proc.getOperation() << endl;
	proc.setOperation(Add);
	cout << proc.getOperation() << endl << endl;

	system("pause");

	return 0;
}

