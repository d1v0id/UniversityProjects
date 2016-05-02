//---------------------------------------------------------------------------

#ifndef UT_p1_10H
#define UT_p1_10H

#include <Classes.hpp>
#include <math.h>
#include <exception>
#include <iostream>
#include <sstream>
#include <ostream>

using namespace std;

class TP1_10
{
public:
        TP1_10(int);
        float DoTransfer(String);
        void SetP(int);
        int GetP();
        int PCharToInt(char);
        int PIntTo10(String);
        float PFracTo10(String);

private:
        int Fp;
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
