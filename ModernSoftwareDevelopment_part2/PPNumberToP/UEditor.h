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
        TEditor(); // инициализирует строку начальным значением
        String Comma(); // добавить запятую к вводимому числу
        String Singe(); // добавить знак к вводимому числу
        String AddZero(); // добавить 0 к вводимому числу
        String Digits(int p); // добавить символ к вводимому числу
        char IntToChar(int p); // число в p-ичный символ
        String Clear(); // удаляет введенное значение - очистка строки
        String Backspace(); // удаляем символ справа
        String GetNumber(); // читает число
        void SetNumber(String number); // записывает число
        int LenNum(); // количество разрядов для представления
        String Edit(int n); // управляет вводом и редактированием
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
