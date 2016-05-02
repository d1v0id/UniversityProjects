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
        
private:
        int Fp;
        int Fa;

        void convert10toBase(int);
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
