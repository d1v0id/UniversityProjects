//---------------------------------------------------------------------------
#ifndef UEditorH
#define UEditorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

const String ZERO_VALUE = "";
const char FRAC_SEPARATOR = '/';
const char NEGATIVE_SIGN = '-';
//---------------------------------------------------------------------------
class TEditor
{
public:
	TEditor();
	~TEditor();
	bool isZeroValue();
	String changeNegativeSign();
	String addNumber(int);
	String addZero();
	String removeNumber();
	String clear();
	String getValue();
	void setValue(const String);

private:
	String value;

	bool checkFormat();
	vector<int> split(const String &, char);
};
//---------------------------------------------------------------------------
#endif
