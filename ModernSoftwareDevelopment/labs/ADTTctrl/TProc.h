#pragma once

enum TOprtn { None, Add, Sub, Mul, Dvd };
enum TFunc { Rev, Sqr };

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

