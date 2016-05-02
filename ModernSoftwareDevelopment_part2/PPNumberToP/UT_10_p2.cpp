//---------------------------------------------------------------------------


#pragma hdrstop

#include "UT_10_p2.h"

T10_P2::T10_P2(int p, int a)
{
        Fp = p;
        Fa = a;
}

String T10_P2::DoTransfer(String number)
{
        String num = number;
        int dig1 = 0;
        double dig2 = 0.0;
        bool neg = false;

        if ((num.Length() > 1) && (num.SubString(1, 1) == "-")) {
                neg = true;
                num = number.SubString(2, number.Length());
        }

        int dotPos = num.Pos(",");

        if (dotPos > 1) {
                dig1 = StrToInt(num.SubString(1, dotPos - 1));
                dig2 = StrToFloat("0," + num.SubString(dotPos + 1, num.Length())); // locale ? (,)
        }
        else {
                dig1 = StrToInt(num);
        }

        String negStr = neg ? "-" : "";

        String newNum1 = convert10toBase(dig1);
        String newNum2 = "0";
        if (dig2 > 0) {
                newNum2 = convertDouble10toBase(dig2);
        }

        if (newNum1.Length() == 0) {
                newNum1 = "0";
        }

        String res = negStr + newNum1 + "," + newNum2;
        return res;
}

String T10_P2::convert10toBase(int dig)
{
        if (dig == 0) {
                return "";
        }

        int x = dig % Fp;
        dig /= Fp;

        if (x < 0) {
                dig++;
        }

        String res = convert10toBase(dig);

        String str = (x < 0) ? x + (Fp * -1) : x;
        if (StrToInt(str) > 9) {
                str = IntToHex(StrToInt(str), 1);
        }

        return res + str;

        //cout << str.c_str();
}

String T10_P2::convertDouble10toBase(double dig)
{
        double d = dig;
        String num = FloatToStr(d);
        int dotPos = num.Pos(","); // locale ? (,)
        String doublePart;

        if (dotPos > 1) {
                doublePart = num.SubString(dotPos + 1, num.Length());
                d = StrToFloat("0," + doublePart);
        }
        else {
                return "";
        }

        double x = d * Fp;

        if ((StrToInt(doublePart) == 0) || (doublePart.Length() == Fa)) {
                return "";
        }

        String res = convertDouble10toBase(x);

        String str = FloatToStr(x);
        dotPos = str.Pos(",");
        if (dotPos > 1) {
                str = str.SubString(1, dotPos - 1);
        }

        if (StrToInt(str) > 9) {
                str = IntToHex(StrToInt(str), 1);
        }

        return str + res;
}

void T10_P2::SetP(int n)
{
        if ((n < 2) || (n > 16)) {
                //throw invalidArgEx;
        }

        Fp = n;
}

int T10_P2::GetP()
{
        return Fp;
}

char T10_P2::IntToPChar(int d)
{
        if ((d < 0) || (d > 9)) {
                //throw invalidArgEx;
        }

        return IntToStr(d)[0];
}

String T10_P2::Int10ToP(int r)
{
        bool neg = (r < 0);
        String negStr = neg ? "-" : "";
        return negStr + convert10toBase(abs(r));
}

String T10_P2::Frac10ToP(String f)
{
        String num = f;
        int dig1 = 0;
        int dig2 = 0;
        bool neg = false;

        if ((num.Length() > 1) && (num.SubString(1, 1) == "-")) {
                neg = true;
                num = f.SubString(2, f.Length());
        }

        int dotPos = num.Pos("/");

        if (dotPos > 1) {
                dig1 = StrToInt(num.SubString(1, dotPos - 1));
                dig2 = StrToInt(num.SubString(dotPos + 1, num.Length()));
        }
        else {
                //throw invalidArgEx;
        }

        String negStr = neg ? "-" : "";

        String newNum1 = convert10toBase(dig1);
        String newNum2 = convert10toBase(dig2);

        if (newNum1.Length() == 0) {
                newNum1 = "0";
        }

        if (newNum2.Length() == 0) {
                //throw invalidArgEx;
        }

        String res = negStr + newNum1 + "/" + newNum2;
        return res;
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
