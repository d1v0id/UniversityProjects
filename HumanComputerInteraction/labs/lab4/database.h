#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlDatabase>

static const QString DB_TYPE = "QSQLITE";
static const QString DB_NAME = "money_management";
static const QString DB_TABLE_NAME = "money_management";
static const QString DB_HOSTNAME = "localhost";

static const QString DB_ALREADY_CREADED_MSG = "Database already created.";
static const QString DB_OPENNED_MSG = "Database openned.";
static const QString DB_OPENING_ERROR_MSG = "Cannot open database: ";
static const QString DB_TABLE_CONTAINS_MSG = "Table already exists.";
static const QString DB_CREATE_TABLE_ERROR_MSG = "Unable to create a table.";
static const QString DB_INSERT_TEST_ROW_ERROR_MSG = "Unable to insert test row into table.";

class Database
{
public:
    static Database &getInstance()
    {
        static Database instance;
        return instance;
    }

    void Create(QString, QString);
    QSqlDatabase getDatabase();

private:
    QSqlDatabase db;
    QString username;
    QString password;

    Database();
};

#endif // DATABASE_H
