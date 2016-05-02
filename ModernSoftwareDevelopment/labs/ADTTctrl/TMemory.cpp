#include "stdafx.h"
#include "TMemory.h"

template <class T = float>
TMemory<T>::TMemory()
{
	init();
}

template <class T = float>
TMemory<T>::~TMemory()
{
}

template <class T = float>
string TMemory<T>::getState()
{
	return StatesHelper::to_string(this->fState);
}

template <class T = float>
T TMemory<T>::getNumber()
{
	return this->fNumber;
}

template <class T = float>
void TMemory<T>::store(const T e)
{
	this->fNumber = e;
	this->fState = States::_On;
}

template <class T = float>
T TMemory<T>::restore()
{
	return (this->fState == States::_On) ? this->fNumber : NULL;
}

template <class T = float>
void TMemory<T>::add(const T e)
{
	if (this->fState == States::_On) {
		this->fNumber = this->fNumber + e;
	}
	else {
		this->store(e);
	}
}

template <class T = float>
void TMemory<T>::clear()
{
	init();
}

template <class T = float>
void TMemory<T>::init()
{
	T number = 0; // Just for test
	this->fNumber = number;
	this->fState = States::_Off;
}
