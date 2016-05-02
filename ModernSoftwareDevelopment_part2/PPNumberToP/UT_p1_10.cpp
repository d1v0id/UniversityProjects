//---------------------------------------------------------------------------


#pragma hdrstop

#include "UT_p1_10.h"

//---------------------------------------------------------------------------
TP1_10::TP1_10(int p)
{
        if (p >= 2 && p <= 16) {
                Fp = p;
        }
        else {
                throw invalidArgEx;
        }
}

float TP1_10::DoTransfer(String number)
{
        // 2356.12 = 2*Fp^3 + 3*Fp^2 + 5*Fp^1 + 6*Fp^0 + 1*Fp^-1 + 2*Fp^-2

        String num = number;
        float dec = 0;
        bool neg = false;

        if ((num.Length() > 1) && (num.SubString(1, 1) == "-")) {
                neg = true;
                num = number.SubString(2, number.Length());
        }

        int dotPos = num.Pos(",") - 1;
        int pVal = num.Length() - 1;
        if (dotPos > 0) {
                pVal -= dotPos + 1;
        }

        for (int i = 1; i <= num.Length(); i++) {
                if (num[i] == ',') {
                        continue;
                }

                int dig = PCharToInt(num.c_str()[i - 1]);

                if (dig > Fp) {
                        throw invalidArgEx;
                }

                dec += dig * pow(Fp, pVal);
                pVal--;
        }

        return neg ? -dec : dec;
}

void TP1_10::SetP(int p)
{
        if (p >= 2 && p <= 16) {
                Fp = p;
        }
        else {
                throw invalidArgEx;
        }
}

int TP1_10::GetP()
{
        return Fp;
}

int TP1_10::PCharToInt(char d)
{
        int dig = 0;

        if (isdigit(d)) {
                dig = StrToInt(d);
        }
        else {
                dig = StrToInt("0x" + String(d));
        }

        return dig;
}

int TP1_10::PIntTo10(String r)
{
        String num = r;
        int dec = 0;
        bool neg = false;

        if ((num.Length() > 1) && (num.SubString(1, 1) == "-")) {
                neg = true;
                num = r.SubString(2, r.Length());
        }

        int pVal = num.Length() - 1;
        if (num.Pos(",") > 0) {
                throw invalidArgEx;
        }

        for (int i = 1; i <= num.Length(); i++) {
                int dig = PCharToInt(num.c_str()[i - 1]);

                if (dig > Fp) {
                        throw invalidArgEx;
                }

                dec += dig * pow(Fp, pVal);
                pVal--;
        }

        return neg ? -dec : dec;
}

float TP1_10::PFracTo10(String f)
{
        String num = f;
        String num1;
        String num2;
        float dec1 = 0;
        float dec2 = 1;
        bool neg = false;

        if ((num.Length() > 1) && (num.SubString(1, 1) == "-")) {
                neg = true;
                num = f.SubString(2, f.Length());
        }

        int dotPos = num.Pos("/");

        if (dotPos > 0) {
                num1 = num.SubString(1, dotPos - 1);
                num2 = num.SubString(dotPos + 1, num.Length());
        }

        dec1 = PIntTo10(num1);
        dec2 = PIntTo10(num2);

        return neg ? -(dec1/dec2) : (dec1/dec2);
}
#pragma package(smart_init)

