#include "moneyutils.h"

const QString MoneyUtils::RUB = "РУБ"; // U+20BD
const QString MoneyUtils::USD = "$";

QString MoneyUtils::valueToMoney(QString value)
{
    return value.replace(",", ".");
}

QString MoneyUtils::moneyToValue(QString value)
{
    return value.replace(".", ",");
}
