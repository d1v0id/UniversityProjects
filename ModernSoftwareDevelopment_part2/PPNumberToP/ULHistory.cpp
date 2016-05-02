//---------------------------------------------------------------------------


#pragma hdrstop

#include "ULHistory.h"

TLHistory::TLHistory()
{
}

void TLHistory::Add(String item)
{
        history.push_back(item);
}

list<String> TLHistory::GetHistory()
{
        return history;
}

int TLHistory::ItemsCount()
{
        return history.size();
}

void TLHistory::clear()
{
        history.clear();
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
