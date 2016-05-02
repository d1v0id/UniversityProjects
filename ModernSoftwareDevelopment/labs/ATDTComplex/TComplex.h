#pragma once
template <class T = float, typename T_INTEGER = int>
class TComplex
{
public:
	TComplex();
	TComplex(T, T);
	TComplex(string);
	TComplex(const TComplex<T> &);
	~TComplex();
	TComplex<T> add(const TComplex<T> &);
	TComplex<T> mul(const TComplex<T> &);
	TComplex<T> sqr();
	TComplex<T> opp();
	TComplex<T> sub(const TComplex<T> &);
	TComplex<T> div(const TComplex<T> &);
	TComplex<T> negative();
	T abs();
	T argRad();
	T arg();
	TComplex<T> pow(T_INTEGER);
	TComplex<T> sqrt(T_INTEGER, T_INTEGER);
	bool equals(const TComplex<T> &);
	bool notEquals(const TComplex<T> &);
	T getRe();
	T getIm();
	string getReAsString();
	string getImAsString();
	string getComplexAsString();

private:
	T a;
	T b;

	void init(T, T);
	vector<T> parseComplex(const string &);
	T pow(T, T_INTEGER);
};

