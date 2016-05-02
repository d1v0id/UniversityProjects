#ifndef OPERATION_H
#define OPERATION_H

#include <QDate>
#include <QString>

class Operation
{
public:
    static const QString DATE_FORMAT;

    Operation(QDate, QString);
    QDate getDate();
    QString getValue();

private:
    QDate date;
    QString value;
};

#endif // OPERATION_H
