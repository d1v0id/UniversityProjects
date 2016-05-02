#ifndef INCOME_H
#define INCOME_H

#include "operation.h"

class Income : public Operation
{
public:
    Income(QDate, QString, QString);
    QString getCategory();

private:
    QString category;
};

#endif // INCOME_H
