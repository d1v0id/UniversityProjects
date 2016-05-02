//---------------------------------------------------------------------------

#include <vcl.h>
#include <UT_10_p2.h>
#include <conio.h>
#include <iostream>
#pragma hdrstop

using namespace std;

//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
        T10_P2* number = new T10_P2(16, 2);
        cout << number->DoTransfer("15.65625").c_str() << endl;

        number = new T10_P2(2, 2);
        cout << number->DoTransfer("6").c_str() << endl;

        number = new T10_P2(2, 5);
        cout << number->DoTransfer("0.375").c_str() << endl;

        number = new T10_P2(16, 4);
        cout << number->DoTransfer("-17.875").c_str() << endl;

        getch();
        return 0;
}
//---------------------------------------------------------------------------
 