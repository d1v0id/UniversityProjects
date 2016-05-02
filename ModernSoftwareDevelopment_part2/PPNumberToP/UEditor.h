//---------------------------------------------------------------------------

#ifndef UEditorH
#define UEditorH

#include <Classes.hpp>
#include <exception>

using namespace std;

const char cFracDivStrPres = ',';
const char cZeroStrPres = '0';
const int cNumLen = 10;
const String cBegString = "0";

class TEditor
{
public:
        TEditor(); // �������������� ������ ��������� ���������
        String Comma(); // �������� ������� � ��������� �����
        String Singe(); // �������� ���� � ��������� �����
        String AddZero(); // �������� 0 � ��������� �����
        String Digits(int p); // �������� ������ � ��������� �����
        char IntToChar(int p); // ����� � p-����� ������
        String Clear(); // ������� ��������� �������� - ������� ������
        String Backspace(); // ������� ������ ������
        String GetNumber(); // ������ �����
        void SetNumber(String number); // ���������� �����
        int LenNum(); // ���������� �������� ��� �������������
        String Edit(int n); // ��������� ������ � ���������������
private:
        String FNumber;
};

class OverSizingInExc: public exception
{
public:
        virtual const char* what() const throw()
        {
                return "Exceeding valid length of number.";
        }
} overSizingInEx;
//---------------------------------------------------------------------------
#endif
