#include "piggybank.h"

const QString Piggybank::IN = "in";

Piggybank::Piggybank(QDate date, QString value, QString direction) : Operation(date, value)
{
    this->direction = direction;
}

QString Piggybank::getDirection()
{
    return direction;
}
