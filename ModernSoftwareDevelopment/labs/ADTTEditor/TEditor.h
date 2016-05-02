#pragma once

const string ZERO_VALUE = "0/1";
const char FRAC_SEPARATOR = '/';
const char NEGATIVE_SIGN = '-';

class TEditor
{
public:
	TEditor();
	~TEditor();
	bool isZeroValue();
	string changeNegativeSign();
	string addNumber(int);
	string addZero();
	string removeNumber();
	string clear();
	string edit(const int cmd);
	string getValue();
	void setValue(const string);

private:
	string value;

	bool checkFormat();
	vector<int> split(const string &, char);
};

