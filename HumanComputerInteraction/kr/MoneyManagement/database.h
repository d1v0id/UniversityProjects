#ifndef DATABASE_H
#define DATABASE_H

#include "income.h"
#include "consumption.h"
#include "piggybank.h"
#include "goals.h"
#include "goal.h"
#include <QSqlDatabase>
#include <QString>
#include <QDate>
#include <QMap>
#include <QStringList>
#include <QList>

class Database
{
public:
    static const QString DB_TYPE;

    static Database &getInstance()
    {
        static Database instance;

        return instance;
    }

    void initilizeDatabase(QSqlDatabase);
    void open(QString, QString);
    void close();
    QString getPiggybankValue(QString);
    QString getWalletValue(QString);
    bool addConsumption(QString, Consumption);
    bool addIncome(QString, Income);
    bool addPiggybank(QString, Piggybank);
    bool sendToGoal(QString, Goals);
    QStringList *getConsumptionCategories(QString);
    QStringList *getIncomeCategories(QString);
    bool setConsumptionCategories(QString, QStringList *);
    bool setIncomeCategories(QString, QStringList *);
    QList<QStringList *> *getConsumptionTemplates(QString);
    QList<QStringList *> *getIncomeTemplates(QString);
    bool setConsumptionTemplates(QString, QList<QStringList *> *);
    bool setIncomeTemplates(QString, QList<QStringList *> *);
    QString getTodayConsumption(QString);
    QString getTodayIncome(QString);
    bool setGoals(QString, QMap<int, Goal>);
    QMap<int, Goal> getGoals(QString);
    QList<Income> getIncomes(QString, QDate, QDate);
    QList<Consumption> getConsumptions(QString, QDate, QDate);
    QList<Piggybank> getPiggybanks(QString, QDate, QDate);
    QList<Goals> getGoals(QString, QDate, QDate);
    QMap<QString, QString> getConsumptionsByCategories(QString);
    QMap<QString, QString> getIncomesByCategories(QString);

private:
    static const QString DB_INCORRECT_CREDENTIALS_MSG;
    static const QString DB_ALREADY_OPENNED_MSG;
    static const QString DB_NAME;
    static const QString DB_HOSTNAME;
    static const QString DB_OPENNED_MSG;
    static const QString DB_CLOSED_MSG;
    static const QString DB_TABLE_EXISTS_MSG;
    static const QString DB_OPEN_ERROR_MSG;
    static const QString DB_CREATE_TABLE_ERROR_MSG;
    static const QString DB_EXECUTE_QUERY_ERROR_MSG;

    static const QString DB_FUND_TABLE;
    static const QString DB_CONSUMPTION_TABLE;
    static const QString DB_INCOME_TABLE;
    static const QString DB_PIGGYBANK_TABLE;
    static const QString DB_GOALS_TABLE;
    static const QString DB_GOALS_LIST_TABLE;
    static const QString DB_CONSUMPTION_CATEGORIES_TABLE;
    static const QString DB_INCOME_CATEGORIES_TABLE;
    static const QString DB_CONSUMPTION_TEMPLATES_TABLE;
    static const QString DB_INCOME_TEMPLATES_TABLE;

    static const QString DB_FUND_TABLE_CREATION_QUERY;
    static const QString DB_CONSUMPTION_TABLE_CREATION_QUERY;
    static const QString DB_INCOME_TABLE_CREATION_QUERY;
    static const QString DB_PIGGYBANK_TABLE_CREATION_QUERY;
    static const QString DB_GOALS_TABLE_CREATION_QUERY;
    static const QString DB_GOALS_LIST_TABLE_CREATION_QUERY;
    static const QString DB_CONSUMPTION_CATEGORIES_TABLE_CREATION_QUERY;
    static const QString DB_INCOME_CATEGORIES_TABLE_CREATION_QUERY;
    static const QString DB_CONSUMPTION_TEMPLATES_TABLE_CREATION_QUERY;
    static const QString DB_INCOME_TEMPLATES_TABLE_CREATION_QUERY;

    QSqlDatabase db;
    QString username;
    QString password;
    QMap<QString, QString> tablesDescriptions;

    Database();
    void createTable(QString, QString);
    QString selectValue(QString, QString, QString);
    bool insertValues(QString, QString, QString);
    QStringList *getCategories(QString, QString);
    bool setCategories(QString, QStringList *, QString);
    QList<QStringList *> *getTemplates(QString, QString);
    bool setTemplates(QString, QList<QStringList *> *, QString);
    void decreaseWalletAmount(QString, QString);
    void increaseWalletAmount(QString, QString);
    void decreasePiggybankAmount(QString, QString);
    void increasePiggybankAmount(QString, QString);
    void setWalletValue(QString, QString);
    void setPiggybankValue(QString, QString);
    void updateFundValue(QString, QString, QString);
    QMap<QString, QString> getValuesByCategories(QString, QString);
};

#endif // DATABASE_H
