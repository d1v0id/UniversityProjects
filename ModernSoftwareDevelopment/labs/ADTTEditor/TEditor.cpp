#include "stdafx.h"
#include "TEditor.h"
#include "EditorException.h"

TEditor::TEditor()
{
	this->value = "";
}

TEditor::~TEditor()
{
}

string TEditor::getValue()
{
	return this->value;
}

void TEditor::setValue(const string value)
{
	this->value = value;
}

bool TEditor::isZeroValue()
{
	return this->value == ZERO_VALUE;
}

string TEditor::changeNegativeSign()
{
	if (this->value[0] == NEGATIVE_SIGN) {
		this->value = this->value.substr(1);
	}
	else {
		this->value = NEGATIVE_SIGN + this->value;
	}

	return this->value;
}

string TEditor::addNumber(int number)
{
	string value = this->value + to_string(number);

	if (checkFormat()) {
		this->value = value;
	}
	else {
		throw EditorException("Incorrect format!");
	}
	
	return this->value;
}

string TEditor::addZero()
{
	return addNumber(0);
}

string TEditor::removeNumber()
{
	unsigned short int n = (this->value[this->value.size() - 3] == FRAC_SEPARATOR) ? 3 : 2;
	this->value = this->value.substr(0, this->value.size() - n);

	return this->value;
}

string TEditor::clear()
{
	this->value = ZERO_VALUE;

	return this->value;
}

string TEditor::edit(const int cmd)
{
	//TODO: execute editor commad

	return this->value;
}

bool TEditor::checkFormat()
{
	vector<int> numbers = split(this->value, FRAC_SEPARATOR);

	if ( (numbers.size() > 2) ||
		 ((numbers.size() == 2) && (numbers.at(1) == 0)) ) {
		return false;
	}

	return true;
}

vector<int> TEditor::split(const string &s, char delim)
{
	stringstream ss(s);
	string item;
	vector<int> elems;
	int number;

	while (getline(ss, item, delim)) {
		stringstream item_ss(item);
		elems.push_back(item_ss >> number ? number : 0);
	}
	return elems;
}
