#include "income.h"

Income::Income(QDate date, QString value, QString category) : Operation(date, value)
{
    this->category = category;
}

QString Income::getCategory()
{
    return category;
}
