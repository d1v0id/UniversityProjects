//---------------------------------------------------------------------------

#ifndef UT_10_p2H
#define UT_10_p2H

#include <Classes.hpp>
#include <iostream>
#include <exception>

using namespace std;

class T10_P2
{
public:
        T10_P2(int, int);
        String DoTransfer(String);
        void SetP(int);
        char IntToPChar(int);
        String Int10ToP(int);
        String Frac10ToP(String);
        
private:
        int Fp;
        int Fa;

        String convert10toBase(int);
        String convertDouble10toBase(double);
};

class InvalidArgExc: public exception
{
public:
        virtual const char* what() const throw()
        {
                return "Invalid Argument";
        }
} invalidArgEx;
//---------------------------------------------------------------------------
#endif
