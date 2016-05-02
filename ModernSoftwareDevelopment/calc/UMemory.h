//---------------------------------------------------------------------------
#ifndef UMemoryH
#define UMemoryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

typedef enum { _On, _Off } States;
//---------------------------------------------------------------------------
template <class T = float>
class TMemory
{
public:
	TMemory();
	~TMemory();
	String getState();
	T getNumber();
	void store(T);
	T restore();
	void add(T);
	void clear();

private:
	void init();

	T fNumber;
	States fState;
};
//---------------------------------------------------------------------------
#endif
