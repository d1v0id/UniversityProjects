#include "consumption.h"

Consumption::Consumption(QDate date, QString value, QString category) : Operation(date, value)
{
    this->category = category;
}

QString Consumption::getCategory()
{
    return category;
}
