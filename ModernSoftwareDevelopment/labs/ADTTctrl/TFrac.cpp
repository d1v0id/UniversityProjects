#include "stdafx.h"
#include "TFrac.h"
#include "CalcException.h"

template <class T = int>
TFrac<T>::TFrac()
{
	init(0, 1);
}

template <class T = int>
TFrac<T>::TFrac(T a, T b)
{
	init(a, b);
}

template <class T = int>
TFrac<T>::TFrac(string frac)
{
	vector<T> numbers = split(frac, '/');
	if (numbers.size() != 2) {
		throw CalcException("Must be two nubers!");
	}

	init(numbers.at(0), numbers.at(1));
}

template <class T = int>
void TFrac<T>::init(T a, T b)
{
	if (is_same<T, float>::value || is_same<T, double>::value) {
		throw CalcException("Incorrect type!");
	}

	if (b == 0) {
		throw CalcException("B equals 0!");
	}

	this->a = a;
	this->b = b;

	reduce();
}

template <class T = int>
TFrac<T>::TFrac(const TFrac<T> &frac)
{
	this->a = frac.a;
	this->b = frac.b;
}

template <class T = int>
TFrac<T>::~TFrac()
{
}

template <class T = int>
T TFrac<T>::getA()
{
	return a;
}

template <class T = int>
T TFrac<T>::getB()
{
	return b;
}

template <class T = int>
string TFrac<T>::getAAsString()
{
	stringstream ss;
	ss << this->a;

	return ss.str();
}

template <class T = int>
string TFrac<T>::getBAsString()
{
	stringstream ss;
	ss << this->b;

	return ss.str();
}

template <class T = int>
string TFrac<T>::getFracAsString()
{
	stringstream ss;
	ss << this->a << "/" << this->b;

	return ss.str();
}

template <class T = int>
TFrac<T> TFrac<T>::add(const TFrac<T> &frac)
{
	T a = this->a * frac.b + frac.a * this->b;
	T b = this->b * frac.b;
	return TFrac<T>(a, b);
}

template <class T = int>
TFrac<T> TFrac<T>::mul(const TFrac<T> &frac)
{
	T a = this->a * frac.a;
	T b = this->b * frac.b;
	return TFrac<T>(a, b);
}

template <class T = int>
TFrac<T> TFrac<T>::sub(const TFrac<T> &frac)
{
	//T nok = this->b * frac.b / calculateGCD(this->b, frac.b);
	//T a = this->a * nok - frac.a * nok;
	//T b = nok;

	// Wrong!
	T a = this->a * frac.b - frac.a * this->b;
	T b = this->b * frac.b;

	return TFrac<T>(a, b);
}

template <class T = int>
TFrac<T> TFrac<T>::div(const TFrac<T> &frac)
{
	T a = this->a * frac.b;
	T b = frac.a * this->b;

	return TFrac<T>(a, b);
}

template <class T = int>
TFrac<T> TFrac<T>::sqr()
{
	T a = this->a * this->a;
	T b = this->b * this->b;

	return TFrac<T>(a, b);
}

template <class T = int>
TFrac<T> TFrac<T>::opp()
{
	return TFrac<T>(this->b, this->a);
}

template <class T = int>
TFrac<T> TFrac<T>::negative()
{
	return TFrac<T>(-this->a, this->b);
}

template <class T = int>
bool TFrac<T>::equals(const TFrac<T> &frac)
{
	return this->a == frac.a && this->b == frac.b;
}

template <class T = int>
bool TFrac<T>::more(const TFrac<T> &frac)
{
	return (this->a / this->b) > (frac.a / frac.b);
}

template <class T = int>
void TFrac<T>::reduce()
{
	T c = calculateGCD(a, b);

	if ((a != 0) && (b != 1) && (c > 1)) {
		a /= c;
		b /= c;
	}

	if (b < 0) {
		a = -a;
		b = -b;
	}
}

template <class T = int>
T TFrac<T>::calculateGCD(T a, T b)
{
	T c;
	while (a != 0) {
		c = a;
		a = b % a;
		b = c;
	}

	return abs(b);
}

template <class T = int>
vector<T> TFrac<T>::split(const string &s, char delim)
{
	stringstream ss(s);
	string item;
	vector<T> elems;
	T number;

	while (getline(ss, item, delim)) {
		stringstream item_ss(item);
		elems.push_back(item_ss >> number ? number : 0);
	}
	return elems;
}
