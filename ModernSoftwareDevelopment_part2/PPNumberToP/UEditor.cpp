//---------------------------------------------------------------------------


#pragma hdrstop

#include "UEditor.h"
TEditor::TEditor() // инициализирует строку начальным значением
{
        FNumber = cZeroStrPres;
}

String TEditor::Comma() // добавить зап€тую к вводимому числу
{
        if (FNumber.Pos(cFracDivStrPres) > 1) {
                return FNumber;
        }

        FNumber += cFracDivStrPres;

        return FNumber;
}

String TEditor::Singe() // добавить знак к вводимому числу
{
        if ((FNumber.Length() > 0) && FNumber != cZeroStrPres) {
                if (FNumber.SubString(1, 1) == "-") {
                        FNumber = FNumber.SubString(2, FNumber.Length());
                }
                else {
                        FNumber = "-" + FNumber;
                }
        }

        return FNumber;
}

String TEditor::AddZero() // добавить 0 к вводимому числу
{
        FNumber += cZeroStrPres;

        //checkValid() // ?

        return FNumber;
}

String TEditor::Digits(int p) // добавить символ к вводимому числу
{
        if ((p < 0) || (p > 15)) {
                throw overSizingInEx;
        }

        if (FNumber == cZeroStrPres) {
                FNumber = "";
        }

        FNumber += String(IntToChar(p));

        //checkValid() // ?

        return FNumber;
}

char TEditor::IntToChar(int p) // число в p-ичный символ
{
        if (p > 9) {
                return IntToHex(p, 1).c_str()[0];
        }

        return IntToStr(p).c_str()[0];
}

String TEditor::Clear() // удал€ет введенное значение - очистка строки
{
        FNumber = cZeroStrPres;

        return FNumber;
}

String TEditor::Backspace() // удал€ем символ справа
{
        if (FNumber.Length() > 1) {
                FNumber = FNumber.SubString(1, FNumber.Length() - 1);
        }
        else if (FNumber.Length() == 1) {
                FNumber = cZeroStrPres;
        }

        return FNumber;
}

String TEditor::GetNumber() // читает число
{
        return FNumber;
}

void TEditor::SetNumber(String number) // записывает число
{
        FNumber = number;
}

int TEditor::LenNum() // количество разр€дов дл€ представлени€
{
        /*if (FNumber.Pos(cFracDivStrPres) > 1) {
                return FNumber.Length() - 1;
        }*/

        return FNumber.Length();
}

String TEditor::Edit(int n) // управл€ет вводом и редактированием
{
        // действи€ по выполнению команды редактировани€ (n)

        return FNumber;
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
