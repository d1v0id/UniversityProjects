#ifndef USERS_H
#define USERS_H

#include "user.h"
#include <QString>

class Users
{
public:
    static bool addUser(User *);
    static User *getUser(QString);
    static bool setUserPassword(QString, QString);
    static bool isValidLoginLength(QString);

private:
    static const int MAX_LOGIN_LENGTH;
    static const long FILE_CRYPTO_KEY;
    static const QString FILE_NAME;
    static const QString FILE_OPEN_ERROR_MSG;
};

#endif // USERS_H
