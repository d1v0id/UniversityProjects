//---------------------------------------------------------------------------
#ifndef UFracH
#define UFracH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;
//---------------------------------------------------------------------------
class TFrac
{
public:
	TFrac();
	TFrac(int, int);
	TFrac(String);
	TFrac(const TFrac &);
	~TFrac();
	int getA();
	int getB();
	String getAAsString();
	String getBAsString();
	String getFracAsString();
	TFrac operator+ (const TFrac &);
	TFrac operator* (const TFrac &);
	TFrac operator- (const TFrac &);
	TFrac operator/ (const TFrac &);
	TFrac sqr();
	TFrac opp();
	TFrac negative();
	bool equals(const TFrac &);
	bool more(const TFrac &);

private:
	int a;
	int b;

	void init(int, int);
	void reduce();
	int calculateGCD(int, int);
	vector<int> split(const String &, char);
};
//---------------------------------------------------------------------------
#endif
