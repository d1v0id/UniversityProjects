#ifndef USERS_H
#define USERS_H

#include <QString>
#include <QStringList>

static const long USERS_FILE_CRYPTO_KEY = 58345082308460135;
static const QString USERS_FILE_NAME = ".users";
static const QString USERS_FILE_OPEN_ERROR_MSG = "Open file error.";
static const QString USERS_FILE_SPLITTER = ":";
static const QString ADMIN_USER = "admin";

class Users
{
public:
    Users();
    bool validate(QString, QString);
    QStringList getUserData(QString);
    bool addUserData(QString, QString, QString, QString);
    bool userCanEdit(QString);
    void setUserPassword(QString, QString);
};

#endif // USERS_H
