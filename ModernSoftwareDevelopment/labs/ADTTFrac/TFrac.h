#pragma once
template <class T = int>
class TFrac
{
public:
	TFrac();
	TFrac(T a, T b);
	TFrac(string frac);
	TFrac(const TFrac<T> &frac);
	~TFrac();
	T getA();
	T getB();
	string getAAsString();
	string getBAsString();
	string getFracAsString();
	TFrac<T> add(const TFrac<T> &frac);
	TFrac<T> mul(const TFrac<T> &frac);
	TFrac<T> sub(const TFrac<T> &frac);
	TFrac<T> div(const TFrac<T> &frac);
	TFrac<T> sqr();
	TFrac<T> opp();
	TFrac<T> negative();
	bool equals(const TFrac<T> &frac);
	bool more(const TFrac<T> &frac);

private:
	T a;
	T b;

	void init(T a, T b);
	void reduce();
	T calculateGCD(T, T);
	vector<T> split(const string &, char);
};
