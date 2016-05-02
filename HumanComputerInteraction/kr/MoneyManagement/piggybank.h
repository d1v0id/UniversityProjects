#ifndef PIGGYBANK_H
#define PIGGYBANK_H

#include "operation.h"

class Piggybank : public Operation
{
public:
    static const QString IN;

    Piggybank(QDate, QString, QString);
    QString getDirection();

private:
    QString direction;
};

#endif // PIGGYBANK_H
