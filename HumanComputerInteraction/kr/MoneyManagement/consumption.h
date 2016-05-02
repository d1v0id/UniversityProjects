#ifndef CONSUMPTION_H
#define CONSUMPTION_H

#include "operation.h"

class Consumption : public Operation
{
public:
    Consumption(QDate, QString, QString);
    QString getCategory();

private:
    QString category;
};

#endif // CONSUMPTION_H
