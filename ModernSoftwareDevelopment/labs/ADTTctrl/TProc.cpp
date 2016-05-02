#include "stdafx.h"
#include "TProc.h"

template <class T = float>
TProc<T>::TProc()
{
	init();
}

template <class T = float>
TProc<T>::~TProc()
{
}

template <class T = float>
T TProc<T>::getLop_Res()
{
	return this->Lop_Res;
}

template <class T = float>
void TProc<T>::setLop_Res(T operand)
{
	this->Lop_Res = operand;
}

template <class T = float>
T TProc<T>::getRop()
{
	return this->Rop;
}

template <class T = float>
void TProc<T>::setRop(T operand)
{
	this->Rop = operand;
}

template <class T = float>
TOprtn TProc<T>::getOperation()
{
	return this->Operation;
}

template <class T = float>
void TProc<T>::setOperation(TOprtn oprtn)
{
	this->Operation = oprtn;
}

template <class T = float>
void TProc<T>::ProcClear()
{
	init();
}

template <class T = float>
void TProc<T>::init()
{
	T value = 0;
	this->Lop_Res = value;
	this->Rop = value;
	this->Operation = None;
}

template <class T = float>
void TProc<T>::OprtnClear()
{
	this->Operation = None;
}

template <class T = float>
void TProc<T>::OprtnRun()
{
	switch (this->Operation) {
	case Add:
		this->Lop_Res.add(this->Rop);
		break;

	case Sub:
		this->Lop_Res.sub(this->Rop);
		break;

	case Mul:
		this->Lop_Res.mul(this->Rop);
		break;

	case Dvd:
		this->Lop_Res.div(this->Rop);
		break;

	case None:
	default:
	}
}

template <class T = float>
void TProc<T>::FuncRun(TFunc func)
{
	switch (func) {
	case Rev:
		this->Rop.rev();
		break;

	case Sqr:
		this->Rop.sqr();
		break;

	default:
	}
}
