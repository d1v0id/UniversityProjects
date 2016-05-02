//---------------------------------------------------------------------------


#pragma hdrstop

#include "UCtrl.h"

TCtrl::TCtrl()
{
        Fe = new TEditor();
        Fc1 = new TP1_10(16);
        Fc2 = new T10_P2(16, 2);
        FState = cEditing;
}

TCtrl::TCtrl(int p)
{
        Fe = new TEditor();
        Fc1 = new TP1_10(p);
        Fc2 = new T10_P2(16, 2);
        FState = cEditing;
}

TCtrl::TCtrl(int p1, int p2)
{
        Fe = new TEditor();
        Fc1 = new TP1_10(p1);
        Fc2 = new T10_P2(p2, 2);
        FState = cEditing;
}

TCtrl::~TCtrl()
{
        delete Fe;
        delete Fc1;
        delete Fc2;
}

String TCtrl::DoCommand(int n)
{
        // в зависимости от значения n и состояния (FState) передает
        // сообщение объекту редактор или преобразователь и изменяет
        // состояние

        // возвращает строку результата либо отредактированное число
        // либо результат преобразования
        switch (n) {
        case cZero:
        case cOne:
        case cTwo:
        case cThree:
        case cFour:
        case cFive:
        case cSix:
        case cSeven:
        case cEight:
        case cNine:
        case cTen:
        case cEleven:
        case cTwelve:
        case cThirteen:
        case cFourteen:
        case cFifteen:
                if (FState == cFinished) {
                        Fe->Clear();
                }
                Fe->Digits(n);
                FState = cEditing;
                break;

        case cComma:
                if (FState == cFinished) {
                        Fe->Clear();
                }
                Fe->Comma();
                FState = cEditing;
                break;

        case cPlusMinus:
                if (FState == cFinished) {
                        Fe->Clear();
                }
                Fe->Singe();
                FState = cEditing;
                break;

        case cBackspace:
                if (FState == cEditing) {
                        Fe->Backspace();
                }
                else {
                        Fe->Clear();
                }
                break;

        case cClear:
                Fe->Clear();
                FState = cFinished;
                break;

        case cPerform:
                String result = Fe->GetNumber();
                if ((Fc1->GetP() != 10) && (Fc2->GetP() != 10)) {
                        result = Fc1->DoTransfer(result);
                        result = Fc2->DoTransfer(result);
                }
                else if ((Fc1->GetP() == 10) && (Fc2->GetP() != 10)) {
                        result = Fc2->DoTransfer(result);
                }
                else if ((Fc1->GetP() != 10) && (Fc2->GetP() == 10)) {
                        result = Fc1->DoTransfer(result);
                }

                FState = cFinished;
                return result;
                break;
        }

        return Fe->GetNumber();
}

void TCtrl::SetState(TState state)
{
        FState = state;
}

TState TCtrl::GetState()
{
        return FState;
}

void TCtrl::SetP_in(int p)
{
        Fc1->SetP(p);
}

int TCtrl::GetP_in()
{
        return Fc1->GetP();
}

void TCtrl::SetP_out(int p)
{
        Fc2->SetP(p);
}

int TCtrl::GetP_out()
{
        return Fc2->GetP();
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
