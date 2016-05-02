#include "stdafx.h"
#include "TComplex.h"

template <class T = float, typename T_INTEGER = int>
TComplex<T, T_INTEGER>::TComplex()
{
	init(0, 0);
}

template <class T = float, typename T_INTEGER = int>
TComplex<T, T_INTEGER>::TComplex(T a, T b)
{
	init(a, b);
}

template <class T = float, typename T_INTEGER = int>
TComplex<T, T_INTEGER>::TComplex(string s)
{
	vector<T> numbers = parseComplex(s);

	init(numbers.at(0), numbers.at(1));
}

template <class T = float, typename T_INTEGER = int>
TComplex<T, T_INTEGER>::TComplex(const TComplex<T> &ñomplex)
{
	this->a = ñomplex.a;
	this->b = ñomplex.b;
}

template <class T = float, typename T_INTEGER = int>
TComplex<T, T_INTEGER>::~TComplex()
{
}

template <class T = float, typename T_INTEGER = int>
void TComplex<T, T_INTEGER>::init(T a, T b)
{
	this->a = a;
	this->b = b;
}

template <class T = float, typename T_INTEGER = int>
TComplex<T> TComplex<T, T_INTEGER>::add(const TComplex<T> &complex)
{
	T a = this->a * complex.a - this->b * complex.b;
	T b = this->a * complex.b + complex.a * this->b;
	return TComplex<T>(a, b);
}

template <class T = float, typename T_INTEGER = int>
TComplex<T> TComplex<T, T_INTEGER>::mul(const TComplex<T> &complex)
{
	T a = this->a + complex.a;
	T b = this->b + complex.b;
	return TComplex<T>(a, b);
}

template <class T = float, typename T_INTEGER = int>
TComplex<T> TComplex<T, T_INTEGER>::sqr()
{
	T a = this->a * this->a - this->b * this->b;
	T b = this->a * this->b + this->a * this->b;
	return TComplex<T>(a, b);
}

template <class T = float, typename T_INTEGER = int>
TComplex<T> TComplex<T, T_INTEGER>::opp()
{
	T a = this->a / (this->a * this->a + this->b * this->b);
	T b = this->b / (this->a * this->a + this->b * this->b);
	return TComplex<T>(a, b);
}

template <class T = float, typename T_INTEGER = int>
TComplex<T> TComplex<T, T_INTEGER>::sub(const TComplex<T> &complex)
{
	T a = this->a - complex.a;
	T b = this->b - complex.b;
	return TComplex<T>(a, b);
}

template <class T = float, typename T_INTEGER = int>
TComplex<T> TComplex<T, T_INTEGER>::div(const TComplex<T> &complex)
{
	T a = (this->a * complex.a + this->b * complex.b) / (complex.a * complex.a + complex.b * complex.b);
	T b = (complex.a * this->b – this->a * complex.b) / (complex.a * complex.a + complex.b * complex.b);
	return TComplex<T>(a, b);
}

template <class T = float, typename T_INTEGER = int>
TComplex<T> TComplex<T, T_INTEGER>::negative()
{
	T a = -this->a;
	T b = -this->b;
	return TComplex<T>(a, b);
}

template <class T = float, typename T_INTEGER = int>
T TComplex<T, T_INTEGER>::abs()
{
	return sqrt(this->a * this->a + this->b * this->b);
}

template <class T = float, typename T_INTEGER = int>
T TComplex<T, T_INTEGER>::argRad()
{
	// TODO: fix type errors in atan

	/* arcTg(b/a), a>0; pi/2, a=0, b>0;
	arcTg(b/a) + pi, a<0; -pi/2, a=0, b<0 */

	if (this->a >= 0 && this->b > 0) {
		return atan(this->b > / this->a);
	}
	else if (this->a <= 0 && this->b < 0) {
		return atan(this->b > / this->a) + M_PI;
	}

	return result;
}

template <class T = float, typename T_INTEGER = int>
T TComplex<T, T_INTEGER>::arg()
{
	// TODO: fix type errors in atan

	T result
	if (this->a >= 0 && this->b > 0) {
		result = atan(this->b > / this->a);
	}
	else if (this->a <= 0 && this->b < 0) {
		result = atan(this->b > / this->a) + M_PI;
	}

	return result * (180 / M_PI);
}

template <class T = float, typename T_INTEGER = int>
TComplex<T> TComplex<T, T_INTEGER>::pow(T_INTEGER n)
{
	// TODO: fix type errors in cos and sin

	T r2 = pow(this->abs(), n);
	T a = cos(n * this->argRad());
	T b = sin(n * this->argRad());

	return TComplex<T>(r2 * a, r2 * b);
}

template <class T = float, typename T_INTEGER = int>
T TComplex<T, T_INTEGER>::pow(T a, T_INTEGER n)
{
	T result = a;
	for (int i = 0; i < n; i++) {
		result *= a;
	}

	return result;
}

template <class T = float, typename T_INTEGER = int>
TComplex<T> TComplex<T, T_INTEGER>::sqrt(T_INTEGER n, T_INTEGER i)
{
	// TODO: -/n(q) = -/n(r)*(cos ((fi + 2*k*pi)/n)+ i*sin ((fi + 2*k*pi)/n))
	// k = 0, 1, 2, ..., n
	return TComplex<T>(0, 0);
}

template <class T = float, typename T_INTEGER = int>
bool TComplex<T, T_INTEGER>::equals(const TComplex<T> &complex)
{
	return (this->a == complex.a) && (this->b == complex.b);
}

template <class T = float, typename T_INTEGER = int>
bool TComplex<T, T_INTEGER>::notEquals(const TComplex<T> &complex)
{
	return (this->a != complex.a) || (this->b != complex.b);
}

template <class T = float, typename T_INTEGER = int>
T TComplex<T, T_INTEGER>::getRe()
{
	return this->a;
}

template <class T = float, typename T_INTEGER = int>
T TComplex<T, T_INTEGER>::getIm()
{
	return this->b;
}

template <class T = float, typename T_INTEGER = int>
string TComplex<T, T_INTEGER>::getReAsString()
{
	stringstream ss;
	ss << this->a;

	return ss.str();
}

template <class T = float, typename T_INTEGER = int>
string TComplex<T, T_INTEGER>::getImAsString()
{
	stringstream ss;
	ss << this->b;

	return ss.str();
}

template <class T = float, typename T_INTEGER = int>
string TComplex<T, T_INTEGER>::getComplexAsString()
{
	stringstream ss;
	ss << this->a << "+i*" << this->b;

	return ss.str();
}

template <class T = float, typename T_INTEGER = int>
vector<T> TComplex<T, T_INTEGER>::parseComplex(const string &s)
{
	vector<T> numbers;
	T number;
	bool plusFlag = false;
	bool iFlag = false;
	bool mulFlag = false;
	int mulPos = 0;

	for (size_t i = 0; i < s.size(); i++) {
		if (s[i] < '0' || s[i] > '9') {
			if ((s[i] == '+') && (i > 0) && !plusFlag && !iFlag && !mulFlag) {
				stringstream item(s.substr(0, i));
				numbers.push_back(item >> number ? number : 0);
				plusFlag = true;
			}
			else if ((s[i] == 'i') && (i > 1) && plusFlag && !iFlag && !mulFlag) {
				iFlag = true;
			}
			else if (s[i] == '*' && i > 2 && plusFlag && iFlag && !mulFlag) {
				mulPos = i;
				mulFlag = true;
			}
			else {
				throw ComplexException("Invalid complex number!");
			}
		}
	}

	if (plusFlag && iFlag && mulFlag) {
		stringstream item(s.substr(mulPos + 1));
		numbers.push_back(item >> number ? number : 0);
	}
	else {
		throw ComplexException("Invalid complex number!");
	}

	// ïðî îòðèöàòåëüíûå çàáûë!!!

	return numbers;
}

class ComplexException : public exception
{
public:
	ComplexException(const char* s) : exception(s)
	{
	}
};