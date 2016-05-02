//---------------------------------------------------------------------------
#pragma hdrstop

#include "UFrac.h"
//---------------------------------------------------------------------------
TFrac::TFrac()
{
	init(0, 1);
}
//---------------------------------------------------------------------------
TFrac::TFrac(int a, int b)
{
	init(a, b);
}
//---------------------------------------------------------------------------
TFrac::TFrac(String frac)
{
	vector<int> numbers = split(frac, '/');

	if (numbers.size() == 2) {
                init(numbers.at(0), numbers.at(1));
	}
        else if (numbers.size() == 1) {
                init(numbers.at(0), 1);
        }
        else {
                init(0, 1);
        }
}
//---------------------------------------------------------------------------
void TFrac::init(int a, int b)
{
	this->a = a;
	this->b = b;

	reduce();
}
//---------------------------------------------------------------------------
TFrac::TFrac(const TFrac &frac)
{
	this->a = frac.a;
	this->b = frac.b;
}
//---------------------------------------------------------------------------
TFrac::~TFrac()
{
}
//---------------------------------------------------------------------------
int TFrac::getA()
{
	return a;
}
//---------------------------------------------------------------------------
int TFrac::getB()
{
	return b;
}
//---------------------------------------------------------------------------
String TFrac::getAAsString()
{
        return IntToStr(this->a);
}
//---------------------------------------------------------------------------
String TFrac::getBAsString()
{
        return IntToStr(this->b);
}
//---------------------------------------------------------------------------
String TFrac::getFracAsString()
{
        return IntToStr(this->a) + "/" + IntToStr(this->b);
}
//---------------------------------------------------------------------------
TFrac TFrac::operator+ (const TFrac &frac)
{
	int a = this->a * frac.b + frac.a * this->b;
	int b = this->b * frac.b;
	return TFrac(a, b);
}
//---------------------------------------------------------------------------
TFrac TFrac::operator* (const TFrac &frac)
{
	int a = this->a * frac.a;
	int b = this->b * frac.b;
	return TFrac(a, b);
}
//---------------------------------------------------------------------------
TFrac TFrac::operator- (const TFrac &frac)
{
	int a = this->a * frac.b - frac.a * this->b;
	int b = this->b * frac.b;

	return TFrac(a, b);
}
//---------------------------------------------------------------------------
TFrac TFrac::operator/ (const TFrac &frac)
{
	int a = this->a * frac.b;
	int b = frac.a * this->b;

	return TFrac(a, b);
}
//---------------------------------------------------------------------------
TFrac TFrac::sqr()
{
	int a = this->a * this->a;
	int b = this->b * this->b;

	return TFrac(a, b);
}
//---------------------------------------------------------------------------
TFrac TFrac::opp()
{
	return TFrac(this->b, this->a);
}
//---------------------------------------------------------------------------
TFrac TFrac::negative()
{
	return TFrac(-this->a, this->b);
}
//---------------------------------------------------------------------------
bool TFrac::equals(const TFrac &frac)
{
	return this->a == frac.a && this->b == frac.b;
}
//---------------------------------------------------------------------------
bool TFrac::more(const TFrac &frac)
{
	return (this->a / this->b) > (frac.a / frac.b);
}
//---------------------------------------------------------------------------
void TFrac::reduce()
{
	int c = calculateGCD(a, b);

	if ((a != 0) && (b != 1) && (c > 1)) {
		a /= c;
		b /= c;
	}

	if (b < 0) {
		a = -a;
		b = -b;
	}
}
//---------------------------------------------------------------------------
int TFrac::calculateGCD(int a, int b)
{
	int c;
	while (a != 0) {
		c = a;
		a = b % a;
		b = c;
	}

	return abs(b);
}
//---------------------------------------------------------------------------
vector<int> TFrac::split(const String &s, char delim)
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
 