#include "database.h"
#include <QtDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtSql>

Database::Database()
{
}

void Database::Create(QString username, QString password)
{
    if (!this->username.isEmpty() || !this->password.isEmpty()) {
        qDebug() << DB_ALREADY_CREADED_MSG;
        return;
    }

    this->username = username;
    this->password = password;
    this->db = QSqlDatabase::addDatabase(DB_TYPE);

    db.setDatabaseName(DB_NAME);
    db.setHostName(DB_HOSTNAME);
    db.setUserName(this->username);
    db.setPassword(this->password);

    if (db.open()) {
        qDebug() << DB_OPENNED_MSG;

        if (db.tables().contains(QLatin1String(DB_TABLE_NAME.toStdString().c_str()))) {
            qDebug() << DB_TABLE_CONTAINS_MSG << endl;
        }
        else {
            QSqlQuery query;
            QString str = "create table " + DB_TABLE_NAME + "("
                "id number primary key not null,"
                "name varchar(40),"
                "money varchar(99));";

            if (!query.exec(str)) {
                qDebug() << DB_CREATE_TABLE_ERROR_MSG;
            }

            str = "insert into " + DB_TABLE_NAME + "(id, name, money) values(1, \"Bob\", \"1234567890\")";

            if (!query.exec(str)) {
                qDebug() << DB_INSERT_TEST_ROW_ERROR_MSG;
            }
        }

        //db.close();
    }
    else {
        qDebug() << DB_OPENING_ERROR_MSG << db.lastError();
    }
}

QSqlDatabase Database::getDatabase()
{
    return this->db;
}
