//---------------------------------------------------------------------------

#ifndef UCtrlH
#define UCtrlH

#include "UEditor.h"
#include "UT_p1_10.h"
#include "UT_10_p2.h"

enum TState
{
        cEditing,
        cFinished
};

enum TCommand
{
        cZero, cOne, cTwo, cThree, cFour, cFive, cSix, cSeven, cEight, cNine,
        cTen, cEleven, cTwelve, cThirteen, cFourteen, cFifteen,
        cComma, cPlusMinus, cBackspace, cClear, cPerform
};

class TCtrl
{
public:
        TCtrl();
        TCtrl(int);
        TCtrl(int, int);
        ~TCtrl();
        String DoCommand(int);
        void SetState(TState);
        TState GetState();
        void SetP_in(int p);
        int GetP_in();
        void SetP_out(int p);
        int GetP_out();

private:
        TEditor* Fe;
        TP1_10* Fc1;
        T10_P2* Fc2;
        TState FState;
};


//---------------------------------------------------------------------------
#endif
