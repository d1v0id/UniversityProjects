//---------------------------------------------------------------------------


#pragma hdrstop

#include "UEditor.h"
TEditor::TEditor() // �������������� ������ ��������� ���������
{
        FNumber = cZeroStrPres;
}

String TEditor::Comma() // �������� ������� � ��������� �����
{
        if (FNumber.Pos(cFracDivStrPres) > 1) {
                return FNumber;
        }

        FNumber += cFracDivStrPres;

        return FNumber;
}

String TEditor::Singe() // �������� ���� � ��������� �����
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

String TEditor::AddZero() // �������� 0 � ��������� �����
{
        FNumber += cZeroStrPres;

        //checkValid() // ?

        return FNumber;
}

String TEditor::Digits(int p) // �������� ������ � ��������� �����
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

char TEditor::IntToChar(int p) // ����� � p-����� ������
{
        if (p > 9) {
                return IntToHex(p, 1).c_str()[0];
        }

        return IntToStr(p).c_str()[0];
}

String TEditor::Clear() // ������� ��������� �������� - ������� ������
{
        FNumber = cZeroStrPres;

        return FNumber;
}

String TEditor::Backspace() // ������� ������ ������
{
        if (FNumber.Length() > 1) {
                FNumber = FNumber.SubString(1, FNumber.Length() - 1);
        }
        else if (FNumber.Length() == 1) {
                FNumber = cZeroStrPres;
        }

        return FNumber;
}

String TEditor::GetNumber() // ������ �����
{
        return FNumber;
}

void TEditor::SetNumber(String number) // ���������� �����
{
        FNumber = number;
}

int TEditor::LenNum() // ���������� �������� ��� �������������
{
        /*if (FNumber.Pos(cFracDivStrPres) > 1) {
                return FNumber.Length() - 1;
        }*/

        return FNumber.Length();
}

String TEditor::Edit(int n) // ��������� ������ � ���������������
{
        // �������� �� ���������� ������� �������������� (n)

        return FNumber;
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
