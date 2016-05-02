#include "users.h"
#include "simplecrypt.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QTextStream>
#include <QDate>

const int Users::MAX_LOGIN_LENGTH = 100;
const long Users::FILE_CRYPTO_KEY = 58345082308460135;
const QString Users::FILE_NAME = ".users";
const QString Users::FILE_OPEN_ERROR_MSG = "Open file error.";

bool Users::addUser(User *user)
{
    SimpleCrypt processSimpleCrypt(FILE_CRYPTO_KEY);
    QFile file(FILE_NAME);

    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream in(&file);

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList userItem = line.split(User::USER_SPLITTER);
            QString rUser = processSimpleCrypt.decryptToString(userItem.value(0));

            if (rUser.compare(user->getLogin()) == 0) {
                return false;
            }
        }

        QStringList userDataList = user->toString().split(User::USER_SPLITTER);
        QString newUserItem = "";

        foreach (QString userDataItem, userDataList) {
            newUserItem += processSimpleCrypt.encryptToString(userDataItem) + User::USER_SPLITTER;
        }

        newUserItem.replace(newUserItem.length() - 1, 1, "\n");
        in << newUserItem;

        file.close();
    }
    else {
        qDebug() << FILE_OPEN_ERROR_MSG << endl;
        return false;
    }

    return true;
}

User *Users::getUser(QString login)
{
    if (!isValidLoginLength(login)) {
        return NULL;
    }

    SimpleCrypt processSimpleCrypt(FILE_CRYPTO_KEY);
    QFile file(FILE_NAME);
    User *user;
    bool valid = false;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList userItem = line.split(User::USER_SPLITTER);
            QString rLogin = processSimpleCrypt.decryptToString(userItem.value(0));

            if ((rLogin.compare(login) == 0) && (userItem.size() == User::FIELDS_COUNT)) {

                QString rPassword = processSimpleCrypt.decryptToString(userItem.value(1));
                QString rQuestion = processSimpleCrypt.decryptToString(userItem.value(2));
                QString rAnswer = processSimpleCrypt.decryptToString(userItem.value(3));
                QString rName = processSimpleCrypt.decryptToString(userItem.value(4));
                QString rSecondName = processSimpleCrypt.decryptToString(userItem.value(5));
                QString rSex = processSimpleCrypt.decryptToString(userItem.value(6));
                QString rBirthDate = processSimpleCrypt.decryptToString(userItem.value(7));
                QString rCurrency = processSimpleCrypt.decryptToString(userItem.value(8));

                user = (new User())->setLogin(rLogin)->setPassword(rPassword)->setQuestion(rQuestion)
                        ->setAnswer(rAnswer)->setName(rName)->setSecondName(rSecondName)
                        ->setSex(rSex)->setBirthDate(QDate::fromString(rBirthDate))->setCurrency(rCurrency);

                valid = true;
                break;
            }
        }

        file.close();
    }
    else {
        qDebug() << FILE_OPEN_ERROR_MSG;
    }

    return valid ? user : NULL;
}

bool Users::setUserPassword(QString login, QString password)
{
    if (!isValidLoginLength(login)) {
        return false;
    }

    SimpleCrypt processSimpleCrypt(FILE_CRYPTO_KEY);
    QFile file(FILE_NAME);

    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QString fileBuffer;
        QTextStream in(&file);

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList userItem = line.split(User::USER_SPLITTER);
            QString rLogin = processSimpleCrypt.decryptToString(userItem.value(0));

            if (rLogin.compare(login) != 0) {
                fileBuffer.append(line + "\n");
            }
            else {
                QString newUserItem = "";

                for (int i = 0; i < userItem.length(); i++) {
                    newUserItem += (i == 1) ? processSimpleCrypt.encryptToString(password) : userItem[i];
                    newUserItem += User::USER_SPLITTER;
                }

                newUserItem.replace(newUserItem.length() - 1, 1, "\n");
                fileBuffer.append(newUserItem);
            }
        }

        file.resize(0);
        in << fileBuffer;

        file.close();
    }
    else {
        qDebug() << FILE_OPEN_ERROR_MSG << endl;
    }

    return true;
}

bool Users::isValidLoginLength(QString login)
{
    return login.length() < MAX_LOGIN_LENGTH;
}
