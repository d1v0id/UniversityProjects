//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "UClcPnl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TClcPnl *ClcPnl;
//---------------------------------------------------------------------------
__fastcall TClcPnl::TClcPnl(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::FormActivate(TObject *Sender)
{
        ClcPnl->SetFocusedControl(ClcPnl);
        STResult->Caption = ctrl.setInitialCalcState(11);
        STMemory->Caption = "";
        shortFormat = false;
}
//---------------------------------------------------------------------------
void TClcPnl::BBClick(int cmdNumber, String rawValue)
{
        FocusControl(0);

        int tmpCmd;
        String result = "";

        switch (cmdNumber) {
        case 0:
                tmpCmd = 100 + StrToInt(rawValue); // commands for number starts from 100
                STResult->Caption = ctrl.executeEditorCmd(tmpCmd);
                ctrl.setCtrlState(cEditing);
                break;

        case 1:
                STResult->Caption = ctrl.executeEditorCmd(cmdNumber);
                ctrl.setCtrlState(cEditing);
                break;

        case 2:
        case 3:
        case 4:
        case 5:
        case 7:
        case 8:
        case 9:
                STResult->Caption = ctrl.executeCalcCmd(cmdNumber, result);

                if (shortFormat) {
                        int length = STResult->Caption.Length();
                        if ((STResult->Caption.Pos("/") == length - 1) && (STResult->Caption[length] == '1')) {
                            STResult->Caption = STResult->Caption.Delete(length - 1, 2);
                        }
                }
                break;

        case 6:
                STResult->Caption = ctrl.executeEditorCmd(cmdNumber);
                ctrl.setCtrlState(cEditing);
                break;

        case 11:
                STResult->Caption = ctrl.setInitialCalcState(cmdNumber);
                STMemory->Caption = "";
                break;

        case 12:
                STResult->Caption = ctrl.executeEditorCmd(cmdNumber);
                ctrl.setCtrlState(cEditing);
                break;

        case 13:
        case 14:
        case 16:
                STMemory->Caption = ctrl.executeMemoryCmd(cmdNumber, result);
                break;

        case 15:
                STResult->Caption = ctrl.executeMemoryCmd(cmdNumber, result);
                ctrl.setCtrlState(cEditing);
                break;
                
        default:
                break;
        }
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BBbsClick(TObject *Sender)
{
        BBClick(10, "BS");
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::MCloseClick(TObject *Sender)
{
        Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::N2Click(TObject *Sender)
{
        shortFormat = true;
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::N3Click(TObject *Sender)
{
        shortFormat = false;        
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::FormCreate(TObject *Sender)
{
        // create TClcCtrl and initialize STResult string 
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BBceClick(TObject *Sender)
{
        BBClick(11, "CE");        
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BBcClick(TObject *Sender)
{
        BBClick(12, "C");        
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BBmcClick(TObject *Sender)
{
        BBClick(16, "MC");        
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BBmrClick(TObject *Sender)
{
        BBClick(15, "MR");        
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BBmsClick(TObject *Sender)
{
        BBClick(14, "MS");        
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BBmplusClick(TObject *Sender)
{
        BBClick(13, "M+");        
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BB7Click(TObject *Sender)
{
        BBClick(0, "7");        
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BB4Click(TObject *Sender)
{
        BBClick(0, "4");
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BB1Click(TObject *Sender)
{
        BBClick(0, "1");        
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BB0Click(TObject *Sender)
{
        BBClick(0, "0");        
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BB8Click(TObject *Sender)
{
        BBClick(0, "8");        
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BB5Click(TObject *Sender)
{
        BBClick(0, "5");        
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BB2Click(TObject *Sender)
{
        BBClick(0, "2");        
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BBplusminusClick(TObject *Sender)
{
        BBClick(1, "+\-");        
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BB9Click(TObject *Sender)
{
        BBClick(0, "9");        
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BB6Click(TObject *Sender)
{
        BBClick(0, "6");        
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BB3Click(TObject *Sender)
{
        BBClick(0, "3");        
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BBslashClick(TObject *Sender)
{
        BBClick(2, "\\");        
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BBdivClick(TObject *Sender)
{
        BBClick(6, "/");
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BBmulClick(TObject *Sender)
{
        BBClick(5, "*");
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BBminusClick(TObject *Sender)
{
        BBClick(4, "-");
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BBplusClick(TObject *Sender)
{
        BBClick(3, "+");
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BBsqrClick(TObject *Sender)
{
        BBClick(9, "sqr");
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BB1xClick(TObject *Sender)
{
        BBClick(8, "1/x");
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::BBcalcClick(TObject *Sender)
{
        BBClick(7, "=");        
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::FormKeyPress(TObject *Sender, char &Key)
{
        switch (Key) {
        case '0':
                BB0->Click();
                break;
        case '1':
                BB1->Click();
                break;
        case '2':
                BB2->Click();
                break;
        case '3':
                BB3->Click();
                break;
        case '4':
                BB4->Click();
                break;
        case '5':
                BB5->Click();
                break;
        case '6':
                BB6->Click();
                break;
        case '7':
                BB7->Click();
                break;
        case '8':
                BB8->Click();
                break;
        case '9':
                BB9->Click();
                break;
        case '+':
                BBplus->Click();
                break;
        case '-':
                BBminus->Click();
                break;
        case '*':
                BBmul->Click();
                break;
        case '/':
                BBdiv->Click();
                break;
        case '=':
                BBcalc->Click();
                break;
        case '\\':
                BBslash->Click();
                break;
        }
}
//---------------------------------------------------------------------------
void __fastcall TClcPnl::MAboutClick(TObject *Sender)
{
        ShowMessage("Калькулятор.\nВыполнил: Коннов Д.А.\nГруппа: ЗП-01");
}
//---------------------------------------------------------------------------

