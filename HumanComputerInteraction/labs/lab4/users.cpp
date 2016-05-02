#include "users.h"
#include "simplecrypt.h"
#include <QtDebug>
#include <QFile>
#include <QStringList>

Users::Users()
{
}

bool Users::validate(QString login, QString passwd)
{
    SimpleCrypt processSimpleCrypt(USERS_FILE_CRYPTO_KEY);
    QFile file(USERS_FILE_NAME);
    bool valid = false;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList userItem = line.split(USERS_FILE_SPLITTER);

            QString rLogin = processSimpleCrypt.decryptToString(userItem.value(0));
            QString rPasswd = processSimpleCrypt.decryptToString(userItem.value(1));

            if ((login.compare(rLogin) == 0) && (passwd.compare(rPasswd) == 0)) {
                valid = true;
                break;
            }
        }

        file.close();
    }
    else {
        qDebug() << USERS_FILE_OPEN_ERROR_MSG;
    }

    return valid;
}

QStringList Users::getUserData(QString login)
{
    SimpleCrypt processSimpleCrypt(USERS_FILE_CRYPTO_KEY);
    QFile file(USERS_FILE_NAME);
    QStringList userData = QStringList();

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList userItem = line.split(USERS_FILE_SPLITTER);
            QString rUser = processSimpleCrypt.decryptToString(userItem.value(0));

            if (rUser.compare(login) == 0) {
                userData.push_back(processSimpleCrypt.decryptToString(userItem.value(1)));
                userData.push_back(processSimpleCrypt.decryptToString(userItem.value(2)));
                userData.push_back(processSimpleCrypt.decryptToString(userItem.value(3)));
                break;
            }
        }

        file.close();
    }
    else {
        qDebug() << USERS_FILE_OPEN_ERROR_MSG << endl;
    }

    return userData;
}

bool Users::userCanEdit(QString login)
{
    return (login == ADMIN_USER);
}

void Users::setUserPassword(QString login, QString password)
{
    SimpleCrypt processSimpleCrypt(USERS_FILE_CRYPTO_KEY);
    QFile file(USERS_FILE_NAME);

    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QString fileBuffer;
        QTextStream in(&file);

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList userItem = line.split(USERS_FILE_SPLITTER);
            QString rUser = processSimpleCrypt.decryptToString(userItem.value(0));

            if (rUser.compare(login) != 0) {
                fileBuffer.append(line + "\n");
            }
            else {
                fileBuffer.append(userItem.value(0) + USERS_FILE_SPLITTER +
                        processSimpleCrypt.encryptToString(password) + USERS_FILE_SPLITTER +
                        userItem.value(2) + USERS_FILE_SPLITTER +
                        userItem.value(3) + "\n");
            }
        }

        file.resize(0);
        in << fileBuffer;

        file.close();
    }
    else {
        qDebug() << USERS_FILE_OPEN_ERROR_MSG << endl;
    }
}

bool Users::addUserData(QString login, QString password, QString question, QString answer)
{
    SimpleCrypt processSimpleCrypt(USERS_FILE_CRYPTO_KEY);
    QFile file(USERS_FILE_NAME);

    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream in(&file);

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList userItem = line.split(USERS_FILE_SPLITTER);
            QString rUser = processSimpleCrypt.decryptToString(userItem.value(0));

            if (rUser.compare(login) == 0) {
                return false;
            }
        }

        QString userData = processSimpleCrypt.encryptToString(login) + USERS_FILE_SPLITTER +
                        processSimpleCrypt.encryptToString(password) + USERS_FILE_SPLITTER +
                        processSimpleCrypt.encryptToString(question) + USERS_FILE_SPLITTER +
                        processSimpleCrypt.encryptToString(answer) + "\n";

        in << userData;

        file.close();
    }
    else {
        qDebug() << USERS_FILE_OPEN_ERROR_MSG << endl;
        return false;
    }

    return true;
}
