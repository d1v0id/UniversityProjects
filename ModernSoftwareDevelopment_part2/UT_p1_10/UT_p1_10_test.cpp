//---------------------------------------------------------------------------

#include <vcl.h>
#include <iostream>
#include <conio.h>
#include <UT_p1_10.h>
#pragma hdrstop

using namespace std;
//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
        /*try {
                TP1_10* wrongNumber = new TP1_10(17);
                cout << wrongNumber->GetP() << endl;
        }
        catch (exception& e) {
                cout << e.what() << endl;
        }*/

        TP1_10* someNumber = new TP1_10(2);
        cout << someNumber->DoTransfer("1001.011") << endl;

        someNumber = new TP1_10(2);
        cout << someNumber->DoTransfer("-1001") << endl;

        someNumber = new TP1_10(7);
        cout << someNumber->DoTransfer("-12345.321") << endl;

        someNumber = new TP1_10(16);
        cout << someNumber->DoTransfer("12AB") << endl;

        someNumber = new TP1_10(16);
        cout << someNumber->DoTransfer("-F.0") << endl;

        someNumber = new TP1_10(2);
        cout << someNumber->DoTransfer("0.1") << endl;

        someNumber = new TP1_10(16);
        cout << someNumber->PFracTo10("5/8") << endl;

        getch();
        return 0;
}
//---------------------------------------------------------------------------
 