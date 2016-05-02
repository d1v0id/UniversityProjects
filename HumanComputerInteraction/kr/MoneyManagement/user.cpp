#include "user.h"

const QString User::USER_SPLITTER = ":";
const int User::FIELDS_COUNT = 10;

User::User()
{
}

User *User::setLogin(QString login)
{
    this->login = login;
    return this;
}

User *User::setPassword(QString password)
{
    this->password = password;
    return this;
}

User *User::setQuestion(QString question)
{
    this->question = question;
    return this;
}

User *User::setAnswer(QString answer)
{
    this->answer = answer;
    return this;
}

User *User::setName(QString name)
{
    this->name = name;
    return this;
}

User *User::setSecondName(QString secondName)
{
    this->secondName = secondName;
    return this;
}

User *User::setSex(QString sex)
{
    this->sex = sex;
    return this;
}

User *User::setBirthDate(QDate birthDate)
{
    this->birthDate = birthDate;
    return this;
}

User *User::setCurrency(QString currency)
{
    this->currency = currency;
    return this;
}

QString User::getLogin()
{
    return login;
}

QString User::getPassword()
{
    return password;
}

QString User::getQuestion()
{
    return question;
}

QString User::getAnswer()
{
    return answer;
}

QString User::getName()
{
    return name;
}

QString User::getSecondName()
{
    return secondName;
}

QString User::getSex()
{
    return sex;
}

QDate User::getBirthDate()
{
    return birthDate;
}

QString User::getCurrency()
{
    return currency;
}

QString User::toString()
{
    return login + USER_SPLITTER +
           password + USER_SPLITTER +
           question + USER_SPLITTER +
           answer + USER_SPLITTER +
           name + USER_SPLITTER +
           secondName + USER_SPLITTER +
           sex + USER_SPLITTER +
           birthDate.toString() + USER_SPLITTER +
           currency + USER_SPLITTER;
}
