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
        int dig2 = 0;
        bool neg = false;

        if ((num.Length() > 1) && (num.SubString(1, 1) == "-")) {
                neg = true;
                num = number.SubString(2, number.Length());
        }

        int dotPos = num.Pos(".");

        if (dotPos > 1) {
                dig1 = StrToInt(num.SubString(1, dotPos - 1));
                dig2 = StrToInt(num.SubString(dotPos + 1, num.Length()));
        }
        else {
                dig1 = StrToInt(num);
        }

        String negStr = neg ? "-" : "";
        cout << negStr.c_str() << dig1 << "," << dig2 << endl;

        convert10toBase(dig1);
}

void T10_P2::convert10toBase(int dig)
{
        if (dig == 0) {
                return;
        }

        int x = dig % Fp;
        dig /= Fp;

        if (x < 0) {
                dig++;
        }

        convert10toBase(dig);

        String str = (x < 0) ? x + (Fp * -1) : x;
        if (StrToInt(str) > 9) {
                str = IntToHex(StrToInt(str), 1);
        }

        cout << str.c_str();
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
