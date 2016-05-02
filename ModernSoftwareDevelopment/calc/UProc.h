//---------------------------------------------------------------------------
#ifndef UProcH
#define UProcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

typedef enum { None, Add, Sub, Mul, Dvd } TOprtn;
typedef enum { Rev, Sqr } TFunc;
//---------------------------------------------------------------------------
template <class T = float>
class TProc
{
public:
	TProc();
	~TProc();
	void ProcClear();
	void OprtnClear();
	void OprtnRun();
	void FuncRun(TFunc);
	T getLop_Res();
	T getRop();
	void setLop_Res(T operand);
	void setRop(T operand);
	TOprtn getOperation();
	void setOperation(TOprtn);

private:
	void init();

	T Lop_Res;
	T Rop;
	TOprtn Operation;
};
//---------------------------------------------------------------------------
#endif
