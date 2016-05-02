//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UPanel_pTop.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TConvPanel *ConvPanel;
//---------------------------------------------------------------------------
__fastcall TConvPanel::TConvPanel(TComponent* Owner)
        : TForm(Owner)
{
        Control = new TCtrl(16);
        History = new TLHistory();
}

void TConvPanel::UpdateSB()
{
        // обновляет командные кнопки для набора цифр p-ичного числа
        int s = Control->GetP_in() - 1;
        for (int i = 0; i < ConvPanel->ControlCount - 1; i++) {
                TControl* ChildControl = ConvPanel->Controls[i];
                if (ChildControl->ClassNameIs("TSpeedButton") &&
                        (ChildControl->Tag < 16) &&
                        (ChildControl->Tag > s)) {
                        ConvPanel->Controls[i]->Enabled = false;
                }
                else {
                        ConvPanel->Controls[i]->Enabled = true;
                }
        }
}

void TConvPanel::DoCommand(int n)
{
        // преобразовать номер команды в вызов метода редактора
        try {
                switch (n) {
                case cComma:
                case cPlusMinus:
                case cBackspace:
                case cClear:
                        StaticText1->Caption = Control->DoCommand(n);
                        StaticText2->Caption = cBegString;
                        break;

                case cPerform:
                        StaticText2->Caption = Control->DoCommand(n);

                        History->Add("Src base: " + IntToStr(Control->GetP_in()) + ";" +
                                " Src value: " + StaticText1->Caption +
                                " Dst base: " + IntToStr(Control->GetP_out()) + ";" +
                                " Dst value: " + StaticText2->Caption);

                        if (StaticText2->Caption.Length() > cNumLen) {
                                // exception Превышена длина результата!
                        }
                        break;

                default:
                        if ((n >= cZero) && (n <= cFifteen)) {
                                StaticText1->Caption = Control->DoCommand(n);
                                if (StaticText1->Caption.Length() > cNumLen) {
                                        // exception Превышено число разрядов!
                                        StaticText2->Caption = cBegString;
                                }
                        }
                }
        }
        catch (InvalidArgExc e) {
        }
        catch (OverSizingInExc e) {
                ShowMessage("Большое число");
                //Control->State = cFinished;
                StaticText1->Caption = Control->DoCommand(cClear);
                StaticText2->Caption = cBegString;
        }
}
//---------------------------------------------------------------------------
void __fastcall TConvPanel::TrackBar1Change(TObject *Sender)
{
        // изменяет значение основания системы счисления и
        // состояния цифровых кнопок на форме
        Control->SetP_in(TrackBar1->Position); // изменяем основание с.сч. в преобразователе
        P_In_Label->Caption = IntToStr(Control->GetP_in());
        Control->SetState(cFinished);
        StaticText1->Caption = "0";
        UpdateSB();
}
//---------------------------------------------------------------------------
void __fastcall TConvPanel::FormCreate(TObject *Sender)
{
        // задает значение основания системы счисления и
        // состояния цифровых кнопок на форме

        TrackBar1->Position = Control->GetP_in();
        P_In_Label->Caption = IntToStr(Control->GetP_in());

        TrackBar2->Position = Control->GetP_out();
        P_Out_Label->Caption = IntToStr(Control->GetP_out());
}
//---------------------------------------------------------------------------
void __fastcall TConvPanel::SpeedButtonClick(TObject *Sender)
{
        int n = ((TControl*) Sender)->Tag; // определить номер команды
        DoCommand(n);
}
//---------------------------------------------------------------------------
void __fastcall TConvPanel::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        int n = -1;

        // здесь преобразование Key в n
        switch (Key) {
        case VK_NUMPAD0:
        case VK_NUMPAD1:
        case VK_NUMPAD2:
        case VK_NUMPAD3:
        case VK_NUMPAD4:
        case VK_NUMPAD5:
        case VK_NUMPAD6:
        case VK_NUMPAD7:
        case VK_NUMPAD8:
        case VK_NUMPAD9:
                n = Key - VK_NUMPAD0;
                break;

        case VK_DECIMAL:
                n = 16;
                break;

        case VK_SUBTRACT:
                n = 17;
                break;

        case VK_BACK:
                n = 18;
                break;

        case VK_DELETE:
                n = 19;
                break;

        case VK_RETURN:
                n = 20;
                break;

        default:
                if ((Key >= 65) && (Key <= 70)) {
                        n = Key - 55; // ???
                }
        }

        DoCommand(n);
}
//---------------------------------------------------------------------------
void __fastcall TConvPanel::TrackBar2Change(TObject *Sender)
{
        Control->SetP_out(TrackBar2->Position); // изменяем основание с.сч. в преобразователе
        P_Out_Label->Caption = IntToStr(Control->GetP_out()); // отображаем значение нового основания с.сч.
        //StaticText2->Caption
        //DoCommand(cPerform); // выполнить преобразование
        StaticText2->Caption = "0";
        Control->SetState(cFinished); // состояние - редактирование завершено
}
//---------------------------------------------------------------------------

void __fastcall TConvPanel::Exit1Click(TObject *Sender)
{
         Close();
}
//---------------------------------------------------------------------------
void __fastcall TConvPanel::About1Click(TObject *Sender)
{
        AboutBox->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TConvPanel::Clear2Click(TObject *Sender)
{
        History->clear();
}
//---------------------------------------------------------------------------
void __fastcall TConvPanel::Clear1Click(TObject *Sender)
{
        list<String> history = History->GetHistory();
        String historyString = "";

        for (list<String>::iterator it = history.begin(); it != history.end(); it++) {
                historyString += (*it) + "\n";
        }

        Application->MessageBox(historyString.c_str(), "History", MB_OK);
}
//---------------------------------------------------------------------------

