#include "operation.h"

const QString Operation::DATE_FORMAT = "yyyy-MM-dd";

Operation::Operation(QDate date, QString value)
{
    this->date = date;
    this->value = value;
}

QDate Operation::getDate()
{
    return date;
}

QString Operation::getValue()
{
    return value;
}
