#ifndef MONEYUTILS_H
#define MONEYUTILS_H

#include <QString>

class MoneyUtils
{
public:
    static const QString RUB;
    static const QString USD;

    static QString valueToMoney(QString);
    static QString moneyToValue(QString);
};

#endif // MONEYUTILS_H
