// ADTTFrac.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TFrac.cpp"

int _tmain(int argc, _TCHAR* argv[])
{
	try {
		//TFrac<float> tFrac1(1.1, 2.1);
		TFrac<int> tFrac2(1.1, 2.1);
		TFrac<> tFrac3(28, 128);
		TFrac<> tFrac4;
		//TFrac<> tFrac5(1, 0);
		TFrac<> tFrac6(0, 2);
		TFrac<> tFrac7("6/3");
		//TFrac<> tFrac8("1/");

		TFrac<> tFrac("6/-3");
		cout << "a = " << tFrac.getA() << endl;
		cout << "b = " << tFrac.getB() << endl << endl;

		//TFrac<> tFracCopy = tFrac;
		//TFrac<> tFracCopy("1/2");
		TFrac<> tFracCopy("1/2");
		cout << "a_copy = " << tFracCopy.getA() << endl;
		cout << "b_copy = " << tFracCopy.getB() << endl << endl;

		TFrac<> tFracAdd = tFrac.add(tFracCopy);
		cout << "a_add = " << tFracAdd.getA() << endl;
		cout << "b_add = " << tFracAdd.getB() << endl << endl;

		TFrac<> tFracMul = tFrac.mul(tFracCopy);
		cout << "a_mul = " << tFracMul.getA() << endl;
		cout << "b_mul = " << tFracMul.getB() << endl << endl;

		TFrac<> tFracSub = tFrac.sub(tFracCopy);
		cout << "a_sub = " << tFracSub.getA() << endl;
		cout << "b_sub = " << tFracSub.getB() << endl << endl;

		TFrac<> tFracDiv = tFrac.div(tFracCopy);
		cout << "a_div = " << tFracDiv.getA() << endl;
		cout << "b_div = " << tFracDiv.getB() << endl << endl;

		TFrac<> tFracSqr = tFrac.sqr();
		cout << "a_sqr = " << tFracSqr.getA() << endl;
		cout << "b_sqr = " << tFracSqr.getB() << endl << endl;

		TFrac<> tFracOpp = tFrac.opp();
		cout << "a_opp = " << tFracOpp.getA() << endl;
		cout << "b_opp = " << tFracOpp.getB() << endl << endl;

		TFrac<> tFracNegative = tFrac.negative();
		cout << "a_negative = " << tFracNegative.getA() << endl;
		cout << "b_negative = " << tFracNegative.getB() << endl << endl;

		bool eq = tFrac.equals(tFracCopy);
		cout << "equals = " << eq << endl << endl;

		bool more = tFrac.more(tFracCopy);
		cout << "more = " << more << endl << endl;

		cout << "a_string = " << tFrac.getAAsString() << endl;
		cout << "b_string = " << tFrac.getBAsString() << endl << endl;

		cout << "frac_string = " << tFrac.getFracAsString() << endl << endl;
	}
	catch (FracException ex) {
		cout << ex.what() << endl;
	}

	system("pause");

	return 0;
}

