//---------------------------------------------------------------------------
#pragma hdrstop

#include "UMemory.h"
//---------------------------------------------------------------------------
template <class T = float>
TMemory<T>::TMemory()
{
	init();
}
//---------------------------------------------------------------------------
template <class T = float>
TMemory<T>::~TMemory()
{
}
//---------------------------------------------------------------------------
template <class T = float>
String TMemory<T>::getState()
{
        return (this->fState == _On) ? "_On" : "_Off";
}
//---------------------------------------------------------------------------
template <class T = float>
T TMemory<T>::getNumber()
{
	return this->fNumber;
}
//---------------------------------------------------------------------------
template <class T = float>
void TMemory<T>::store(T e)
{
	this->fNumber = e;
	this->fState = _On;
}
//---------------------------------------------------------------------------
template <class T = float>
T TMemory<T>::restore()
{
        T empty;
	return (this->fState == _On) ? this->fNumber : empty;
}
//---------------------------------------------------------------------------
template <class T = float>
void TMemory<T>::add(T e)
{
	if (this->fState == _On) {
		this->fNumber = this->fNumber + e;
	}
	else {
		this->store(e);
	}
}
//---------------------------------------------------------------------------
template <class T = float>
void TMemory<T>::clear()
{
	init();
}
//---------------------------------------------------------------------------
template <class T = float>
void TMemory<T>::init()
{
        T number;
	this->fNumber = number;
	this->fState = _Off;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
 