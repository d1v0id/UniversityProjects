//---------------------------------------------------------------------------

#ifndef ULHistoryH
#define ULHistoryH

#include <Classes.hpp>
#include <list>

using namespace std;

class TLHistory
{
public:
        TLHistory();
        void Add(String);
        list<String> GetHistory();
        int ItemsCount();
        void clear();

private:
        list<String> history;
};
//---------------------------------------------------------------------------
#endif
