#ifndef USER_H
#define USER_H

#include <QDate>
#include <QString>

class User
{
public:
    static const QString USER_SPLITTER;
    static const int FIELDS_COUNT;

    User();
    User *setLogin(QString);
    User *setPassword(QString);
    User *setQuestion(QString);
    User *setAnswer(QString);
    User *setName(QString);
    User *setSecondName(QString);
    User *setSex(QString);
    User *setBirthDate(QDate);
    User *setCurrency(QString);
    QString getLogin();
    QString getPassword();
    QString getQuestion();
    QString getAnswer();
    QString getName();
    QString getSecondName();
    QString getSex();
    QDate getBirthDate();
    QString getCurrency();
    QString toString();

private:
    QString login;
    QString password;
    QString question;
    QString answer;
    QString name;
    QString secondName;
    QString sex;
    QDate birthDate;
    QString currency;
};

#endif // USER_H
