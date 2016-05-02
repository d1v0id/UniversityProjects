//---------------------------------------------------------------------------
#pragma hdrstop

#include "UEditor.h"
//---------------------------------------------------------------------------
TEditor::TEditor()
{
	this->value = "";
}
//---------------------------------------------------------------------------
TEditor::~TEditor()
{
}
//---------------------------------------------------------------------------
String TEditor::getValue()
{
	return this->value;
}
//---------------------------------------------------------------------------
void TEditor::setValue(const String value)
{
	this->value = value;
}
//---------------------------------------------------------------------------
bool TEditor::isZeroValue()
{
	return this->value == ZERO_VALUE;
}
//---------------------------------------------------------------------------
String TEditor::changeNegativeSign()
{
        if (this->value.IsEmpty()) {
                return "";
        }
        
	if (this->value[1] == NEGATIVE_SIGN) { // this is C++ Builder motherfucker!
		this->value = this->value.SubString(2, this->value.Length());
	}
	else {
		this->value = AnsiString(NEGATIVE_SIGN) + this->value;
	}

	return this->value;
}
//---------------------------------------------------------------------------
String TEditor::addNumber(int number)
{
        String tmpValue = this->value;
        this->value = this->value + IntToStr(number);

	if (!checkFormat()) {
                this->value = tmpValue;
	}

	return this->value;
}
//---------------------------------------------------------------------------
String TEditor::addZero()
{
	return addNumber(0);
}
//---------------------------------------------------------------------------
String TEditor::removeNumber()
{
	unsigned short int n = (this->value[this->value.Length() - 3] == FRAC_SEPARATOR) ? 3 : 2;
	this->value = this->value.SubString(0, this->value.Length() - n);

	return this->value;
}
//---------------------------------------------------------------------------
String TEditor::clear()
{
	this->value = ZERO_VALUE;

	return this->value;
}
//---------------------------------------------------------------------------
bool TEditor::checkFormat()
{
	vector<int> numbers = split(this->value, FRAC_SEPARATOR);

	if ((numbers.size() > 2) ||
		((numbers.size() == 2) && (numbers.at(1) == 0))) {
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
vector<int> TEditor::split(const String &s, char delim)
{
        TStringList* pList = new TStringList();
        pList->Delimiter = delim;
        pList->DelimitedText = s;

        vector<int> elems;
        int number;

        for (int i = 0; i < pList->Count; i++) {
                elems.push_back(StrToInt(pList->Strings[i]));
        }

        return elems;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
