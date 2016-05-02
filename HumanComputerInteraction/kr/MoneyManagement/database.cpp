#include "database.h"
#include "moneyutils.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QMapIterator>
#include <QPixmap>
#include <QBuffer>

const QString Database::DB_TYPE = "QSQLITE";

const QString Database::DB_INCORRECT_CREDENTIALS_MSG = "Incorrect credentials.";
const QString Database::DB_ALREADY_OPENNED_MSG = "Database already created.";
const QString Database::DB_NAME = "money_management";
const QString Database::DB_HOSTNAME = "localhost";
const QString Database::DB_OPENNED_MSG = "Database openned.";
const QString Database::DB_CLOSED_MSG = "Database closed.";
const QString Database::DB_TABLE_EXISTS_MSG = " table exists.";
const QString Database::DB_OPEN_ERROR_MSG = "Cannot open database: ";
const QString Database::DB_CREATE_TABLE_ERROR_MSG = "Unable to create a table.";
const QString Database::DB_EXECUTE_QUERY_ERROR_MSG = "Unable to execute query: ";

const QString Database::DB_FUND_TABLE = "fund";
const QString Database::DB_CONSUMPTION_TABLE = "consumption";
const QString Database::DB_INCOME_TABLE = "income";
const QString Database::DB_PIGGYBANK_TABLE = "piggybank";
const QString Database::DB_GOALS_TABLE = "goals";
const QString Database::DB_GOALS_LIST_TABLE = "goals_list";
const QString Database::DB_CONSUMPTION_CATEGORIES_TABLE = "consumption_categories";
const QString Database::DB_INCOME_CATEGORIES_TABLE = "income_categories";
const QString Database::DB_CONSUMPTION_TEMPLATES_TABLE = "consumption_templates";
const QString Database::DB_INCOME_TEMPLATES_TABLE = "income_templates";

const QString Database::DB_FUND_TABLE_CREATION_QUERY = "login varchar(100) primary key not null, piggybank_amount varchar(50), wallet_amount varchar(50), flags varchar(10)";
const QString Database::DB_CONSUMPTION_TABLE_CREATION_QUERY = "id integer primary key autoincrement not null, login varchar(100) not null, op_date date not null, value varchar(50) not null, category varchar(150) not null, flags varchar(10)";
const QString Database::DB_INCOME_TABLE_CREATION_QUERY = "id integer primary key autoincrement not null, login varchar(100) not null, op_date date not null, value varchar(50) not null, category varchar(150) not null, flags varchar(10)";
const QString Database::DB_PIGGYBANK_TABLE_CREATION_QUERY = "id integer primary key autoincrement not null, login varchar(100) not null, op_date date not null, value varchar(50), direction varchar(3) not null, flags varchar(10)";
const QString Database::DB_GOALS_TABLE_CREATION_QUERY = "id integer primary key autoincrement not null, login varchar(100) not null, op_date date not null, value varchar(50), goal_id integer not null, flags varchar(10)";
const QString Database::DB_GOALS_LIST_TABLE_CREATION_QUERY = "id integer primary key autoincrement not null, login varchar(100) not null, caption varchar(150) not null, text varchar(1000), image blob, cost varchar(50), balance varchar(50), state varchar(12) not null, flags varchar(10)";
const QString Database::DB_CONSUMPTION_CATEGORIES_TABLE_CREATION_QUERY = "id integer primary key autoincrement not null, text varchar(150) not null, login varchar(100) not null, flags varchar(10)";
const QString Database::DB_INCOME_CATEGORIES_TABLE_CREATION_QUERY = "id integer primary key autoincrement not null, text varchar(150) not null, login varchar(100) not null, flags varchar(10)";
const QString Database::DB_CONSUMPTION_TEMPLATES_TABLE_CREATION_QUERY = "id integer primary key autoincrement not null, login varchar(100) not null, value varchar(50) not null, category varchar(150) not null, flags varchar(10)";
const QString Database::DB_INCOME_TEMPLATES_TABLE_CREATION_QUERY = "id integer primary key autoincrement not null, login varchar(100) not null, value varchar(50) not null, category varchar(150) not null, flags varchar(10)";

Database::Database()
{
    tablesDescriptions.insert(DB_FUND_TABLE, DB_FUND_TABLE_CREATION_QUERY);
    tablesDescriptions.insert(DB_CONSUMPTION_TABLE, DB_CONSUMPTION_TABLE_CREATION_QUERY);
    tablesDescriptions.insert(DB_INCOME_TABLE, DB_INCOME_TABLE_CREATION_QUERY);
    tablesDescriptions.insert(DB_PIGGYBANK_TABLE, DB_PIGGYBANK_TABLE_CREATION_QUERY);
    tablesDescriptions.insert(DB_GOALS_TABLE, DB_GOALS_TABLE_CREATION_QUERY);
    tablesDescriptions.insert(DB_GOALS_LIST_TABLE, DB_GOALS_LIST_TABLE_CREATION_QUERY);
    tablesDescriptions.insert(DB_CONSUMPTION_CATEGORIES_TABLE, DB_CONSUMPTION_CATEGORIES_TABLE_CREATION_QUERY);
    tablesDescriptions.insert(DB_INCOME_CATEGORIES_TABLE, DB_INCOME_CATEGORIES_TABLE_CREATION_QUERY);
    tablesDescriptions.insert(DB_CONSUMPTION_TEMPLATES_TABLE, DB_CONSUMPTION_TEMPLATES_TABLE_CREATION_QUERY);
    tablesDescriptions.insert(DB_INCOME_TEMPLATES_TABLE, DB_INCOME_TEMPLATES_TABLE_CREATION_QUERY);
}

void Database::initilizeDatabase(QSqlDatabase database)
{
    this->db = database;
}

void Database::open(QString username, QString password)
{
    if (username.isEmpty() || password.isEmpty()) {
        qDebug() << DB_INCORRECT_CREDENTIALS_MSG;
        return;
    }

    if (!this->username.isEmpty() || !this->password.isEmpty()) {
        qDebug() << DB_ALREADY_OPENNED_MSG;
        return;
    }

    this->username = username;
    this->password = password;

    db.setDatabaseName(DB_NAME);
    db.setHostName(DB_HOSTNAME);
    db.setUserName(this->username);
    db.setPassword(this->password);

    if (db.open()) {
        qDebug() << DB_OPENNED_MSG;
        QMapIterator<QString, QString> it(tablesDescriptions);

        while (it.hasNext()) {
            it.next();

            if (db.tables().contains(QLatin1String(it.key().toStdString().c_str()))) {
                qDebug() << it.key() + DB_TABLE_EXISTS_MSG;
            }
            else {
                createTable(it.key(), it.value());
            }
        }
    }
    else {
        qDebug() << DB_OPEN_ERROR_MSG << db.lastError();
    }
}

void Database::close()
{
    qDebug() << DB_CLOSED_MSG;
    db.close();
}

void Database::createTable(QString table, QString query)
{
    QSqlQuery sqlQuery;
    QString createQuery = "create table " + table + "(" + query + ");";

    if (!sqlQuery.exec(createQuery)) {
        qDebug() << DB_CREATE_TABLE_ERROR_MSG;
    }
}

QString Database::getPiggybankValue(QString login)
{
    return selectValue("piggybank_amount", DB_FUND_TABLE, "login=\"" + login + "\"");
}

QString Database::getWalletValue(QString login)
{
    return selectValue("wallet_amount", DB_FUND_TABLE, "login=\"" + login + "\"");
}

QString Database::selectValue(QString value, QString table, QString filter)
{
    QSqlQuery query;
    QString selectQuery = "select " + value + " from " + table + " where " + filter + ";";
    QString result = "";

    if (query.exec(selectQuery)) {
        if (query.next()) {
            result = query.value(query.record().indexOf(value)).toString();
        }
    }
    else {
        qDebug() << DB_EXECUTE_QUERY_ERROR_MSG + selectQuery;
    }

    return result;
}

bool Database::addConsumption(QString login, Consumption consumption)
{
    QString value = MoneyUtils::valueToMoney(consumption.getValue());

    QString fields = "login, op_date, value, category";
    QString values = "\"" + login + "\", \"" +
                     consumption.getDate().toString("yyyy-MM-dd") + "\", \"" +
                     value + "\", \"" +
                     consumption.getCategory() + "\"";

    bool result = insertValues(DB_CONSUMPTION_TABLE, fields, values);

    if (result) {
        decreaseWalletAmount(login, value);
    }

    return result;
}

bool Database::addIncome(QString login, Income income)
{
    QString value = MoneyUtils::valueToMoney(income.getValue());

    QString fields = "login, op_date, value, category";
    QString values = "\"" + login + "\", \"" +
                     income.getDate().toString("yyyy-MM-dd") + "\", \"" +
                     value + "\", \"" +
                     income.getCategory() + "\"";

    bool result = insertValues(DB_INCOME_TABLE, fields, values);

    if (result) {
        increaseWalletAmount(login, value);
    }

    return result;
}

bool Database::addPiggybank(QString login, Piggybank piggybank)
{
    QString value = MoneyUtils::valueToMoney(piggybank.getValue());

    QString fields = "login, op_date, value, direction";
    QString values = "\"" + login + "\", \"" +
                     piggybank.getDate().toString("yyyy-MM-dd") + "\", \"" +
                     value + "\", \"" +
                     piggybank.getDirection() + "\"";

    bool result = insertValues(DB_PIGGYBANK_TABLE, fields, values);

    if (result) {
        increasePiggybankAmount(login, value);
        decreaseWalletAmount(login, value);
    }

    return result;
}

bool Database::sendToGoal(QString login, Goals goals)
{
    QString value = MoneyUtils::valueToMoney(goals.getValue());

    QString fields = "login, op_date, value, goal_id";
    QString values = "\"" + login + "\", \"" +
                     goals.getDate().toString("yyyy-MM-dd") + "\", \"" +
                     value + "\", " +
                     QString::number(goals.getGoalId());

    bool result = insertValues(DB_GOALS_TABLE, fields, values);

    if (result) {
        decreasePiggybankAmount(login, value);

        QSqlQuery query;
        QString selectQuery = "select * from " + DB_GOALS_LIST_TABLE + " where login=\"" + login + "\" and id=" + QString::number(goals.getGoalId()) + ";";

        if (query.exec(selectQuery) && query.next()) {
            QString balanceValue = query.value(query.record().indexOf("balance")).toString();
            double costValue = query.value(query.record().indexOf("cost")).toDouble();
            QString newBalanceValue = QString::number(balanceValue.toDouble() + value.toDouble());
            QString updateQuery = "update " + DB_GOALS_LIST_TABLE + " set balance=\"" + MoneyUtils::valueToMoney(newBalanceValue) + "\"";

            if (newBalanceValue.toDouble() >= costValue) {
               updateQuery += ", state=\"ACHIEVED\"";
            }

            updateQuery += " where id=" + QString::number(goals.getGoalId()) + ";";

            if (!query.exec(updateQuery)) {
                qDebug() << DB_EXECUTE_QUERY_ERROR_MSG + updateQuery;
            }
        }
    }

    return result;
}

bool Database::insertValues(QString table, QString fields, QString values)
{
    QSqlQuery query;
    QString insertQuery = "insert into " + table + "(" + fields + ") values(" + values + ");";
    bool result = query.exec(insertQuery);

    if (!result) {
        qDebug() << DB_EXECUTE_QUERY_ERROR_MSG + insertQuery;
    }

    return result;
}

QStringList *Database::getConsumptionCategories(QString login)
{
    return getCategories(login, DB_CONSUMPTION_CATEGORIES_TABLE);
}

QStringList *Database::getIncomeCategories(QString login)
{
    return getCategories(login, DB_INCOME_CATEGORIES_TABLE);
}

QStringList *Database::getCategories(QString login, QString type)
{
    QStringList *categories = new QStringList();

    QSqlQuery query;
    QString selectQuery = "select id, text from " + type + " where login=\"" + login + "\" order by id;";

    if (query.exec(selectQuery)) {
        while (query.next()) {
            QString category = query.value(query.record().indexOf("text")).toString();
            categories->append(category);
        }
    }
    else {
        qDebug() << DB_EXECUTE_QUERY_ERROR_MSG + selectQuery;
    }

    return categories;
}

bool Database::setConsumptionCategories(QString login, QStringList *categories)
{
    return setCategories(login, categories, DB_CONSUMPTION_CATEGORIES_TABLE);
}

bool Database::setIncomeCategories(QString login, QStringList *categories)
{
    return setCategories(login, categories, DB_INCOME_CATEGORIES_TABLE);
}

bool Database::setCategories(QString login, QStringList *categories, QString type)
{
    QSqlQuery query;
    QString deleteQuery = "delete from " + type + " where login=\"" + login + "\";";

    if (!query.exec(deleteQuery)) {
        qDebug() << DB_EXECUTE_QUERY_ERROR_MSG + deleteQuery;
        return false;
    }

    foreach (QString category, *categories) {
        QString insertQuery = "insert into " + type + "(text, login) values(\"" + category + "\", \"" + login + "\");";
        if (!query.exec(insertQuery)) {
            qDebug() << DB_EXECUTE_QUERY_ERROR_MSG + insertQuery;
            return false;
        }
    }

    return true;
}

QList<QStringList *> *Database::getConsumptionTemplates(QString login)
{
    return getTemplates(login, DB_CONSUMPTION_TEMPLATES_TABLE);
}

QList<QStringList *> *Database::getIncomeTemplates(QString login)
{
    return getTemplates(login, DB_INCOME_TEMPLATES_TABLE);
}

QList<QStringList *> *Database::getTemplates(QString login, QString type)
{
    QList<QStringList *> *templates = new QList<QStringList *>();

    QSqlQuery query;
    QString selectQuery = "select id, value, category from " + type + " where login=\"" + login + "\" order by id;";

    if (query.exec(selectQuery)) {
        while (query.next()) {
            QStringList *templateItem = new QStringList();
            QString value = query.value(query.record().indexOf("value")).toString();
            QString category = query.value(query.record().indexOf("category")).toString();
            templateItem->append(value);
            templateItem->append(category);
            templates->append(templateItem);
        }
    }
    else {
        qDebug() << DB_EXECUTE_QUERY_ERROR_MSG + selectQuery;
    }

    return templates;
}

bool Database::setConsumptionTemplates(QString login, QList<QStringList *> *templates)
{
    return setTemplates(login, templates, DB_CONSUMPTION_TEMPLATES_TABLE);
}

bool Database::setIncomeTemplates(QString login, QList<QStringList *> *templates)
{
    return setTemplates(login, templates, DB_INCOME_TEMPLATES_TABLE);
}

bool Database::setTemplates(QString login, QList<QStringList *> *templates, QString type)
{
    QSqlQuery query;
    QString deleteQuery = "delete from " + type + " where login=\"" + login + "\";";

    if (!query.exec(deleteQuery)) {
        qDebug() << DB_EXECUTE_QUERY_ERROR_MSG + deleteQuery;
        return false;
    }

    foreach (QStringList *templateItem, *templates) {
        QString insertQuery = "insert into " + type + "(value, category, login) values(\"" +
                templateItem->at(0) + "\", \"" + templateItem->at(1) + "\", \"" + login + "\");";

        if (!query.exec(insertQuery)) {
            qDebug() << DB_EXECUTE_QUERY_ERROR_MSG + insertQuery;
            return false;
        }
    }

    return true;
}

void Database::decreaseWalletAmount(QString login, QString value)
{
    QString newValue = QString::number(getWalletValue(login).toDouble() - value.toDouble());
    newValue = MoneyUtils::valueToMoney(newValue);
    setWalletValue(login, newValue);
}

void Database::increaseWalletAmount(QString login, QString value)
{
    QString newValue = QString::number(getWalletValue(login).toDouble() + value.toDouble());
    newValue = MoneyUtils::valueToMoney(newValue);
    setWalletValue(login, newValue);
}

void Database::decreasePiggybankAmount(QString login, QString value)
{
    QString newValue = QString::number(getPiggybankValue(login).toDouble() - value.toDouble());
    newValue = MoneyUtils::valueToMoney(newValue);
    setPiggybankValue(login, newValue);
}

void Database::increasePiggybankAmount(QString login, QString value)
{
    QString newValue = QString::number(getPiggybankValue(login).toDouble() + value.toDouble());
    newValue = MoneyUtils::valueToMoney(newValue);
    setPiggybankValue(login, newValue);
}

void Database::setWalletValue(QString login, QString value)
{
    value = MoneyUtils::valueToMoney(value);
    updateFundValue(login, "wallet_amount", value);
}

void Database::setPiggybankValue(QString login, QString value)
{
    value = MoneyUtils::valueToMoney(value);
    updateFundValue(login, "piggybank_amount", value);
}

void Database::updateFundValue(QString login, QString field, QString value)
{
    value = MoneyUtils::valueToMoney(value);

    QSqlQuery query;
    QString selectQuery = "select * from " + DB_FUND_TABLE + " where login=\"" + login + "\";";

    if (query.exec(selectQuery) && query.next()) {
        QString updateQuery = "update " + DB_FUND_TABLE + " set " + field + "=\"" + value + "\" where login=\"" + login + "\";";

        if (!query.exec(updateQuery)) {
            qDebug() << DB_EXECUTE_QUERY_ERROR_MSG + updateQuery;
        }
    }
    else {
        QString insertQuery = "insert into " + DB_FUND_TABLE + "(login, " + field + ", flags) values (\"" + login + "\", \"" + value + "\", \"\");";

        if (!query.exec(insertQuery)) {
            qDebug() << DB_EXECUTE_QUERY_ERROR_MSG + insertQuery;
        }
    }
}

QString Database::getTodayConsumption(QString login)
{
    double value = 0;
    QList<Consumption> consumptions = getConsumptions(login, QDate::currentDate(), QDate::currentDate());

    foreach (Consumption consumption, consumptions) {
        value += consumption.getValue().toDouble();
    }

    return MoneyUtils::valueToMoney(QString::number(value));
}

QString Database::getTodayIncome(QString login)
{
    double value = 0;
    QList<Income> incomes = getIncomes(login, QDate::currentDate(), QDate::currentDate());

    foreach (Income income, incomes) {
        value += income.getValue().toDouble();
    }

    return MoneyUtils::valueToMoney(QString::number(value));
}

bool Database::setGoals(QString login, QMap<int, Goal> goals)
{
    QMap<int, Goal> currentGoals = getGoals(login);
    QMapIterator<int, Goal> it(currentGoals);

    while (it.hasNext()) {
        it.next();

        if (goals.contains(it.key())) {
            Goal goal = goals.value(it.key());
            int id = goal.getId();
            QString caption = goal.getCaption();
            QString text = goal.getText();
            QString cost = goal.getCost();
            QString balance = goal.getBalance();
            QString state = goal.getState();
            QString flags = goal.getFlags();

            QPixmap image = goal.getImage();
            QByteArray imageByteArray;
            QBuffer buffer(&imageByteArray);

            buffer.open(QIODevice::WriteOnly);
            image.save(&buffer, "PNG");

            QSqlQuery query;
            QString updateQuery = "update " + DB_GOALS_LIST_TABLE +
                    " set login=:login, caption=:caption, text=:text, cost=:cost, balance=:balance, state=:state, flags=:flags where id=:id;"; // image=:image

            query.prepare(updateQuery);
            query.bindValue(":id", id);
            query.bindValue(":login", login);
            query.bindValue(":caption", caption);
            query.bindValue(":text", text);
            query.bindValue(":image", imageByteArray);
            query.bindValue(":cost", cost);
            query.bindValue(":balance", balance);
            query.bindValue(":state", state);
            query.bindValue(":flags", flags);

            if (!query.exec()) {
                qDebug() << DB_EXECUTE_QUERY_ERROR_MSG + updateQuery;
                qDebug() << query.lastError();
                return false;
            }

            goals.remove(it.key());
        }
    }

    QMapIterator<int, Goal> newGoalsIt(goals);

    while (newGoalsIt.hasNext()) {
        newGoalsIt.next();

        Goal goal = newGoalsIt.value();
        QString caption = goal.getCaption();
        QString text = goal.getText();
        QString cost = goal.getCost();
        QString balance = goal.getBalance();
        QString state = goal.getState();

        QPixmap image = goal.getImage();
        QByteArray imageByteArray;
        QBuffer buffer(&imageByteArray);

        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG");

        QSqlQuery query;
        QString insertQuery = "insert into " + DB_GOALS_LIST_TABLE + "(login, caption, text, image, cost, balance, state, flags) "
              "values(:login, :caption, :text, :image, :cost, :balance, :state, :flags);";

        query.prepare(insertQuery);
        query.bindValue(":login", login);
        query.bindValue(":caption", caption);
        query.bindValue(":text", text);
        query.bindValue(":image", imageByteArray);
        query.bindValue(":cost", cost);
        query.bindValue(":balance", balance);
        query.bindValue(":state", state);
        query.bindValue(":flags", "");

        if (!query.exec()) {
            qDebug() << DB_EXECUTE_QUERY_ERROR_MSG + insertQuery;
            qDebug() << query.lastError();
            return false;
        }
    }

    return true;
}

QMap<int, Goal> Database::getGoals(QString login)
{
    QMap<int, Goal> goals;

    QSqlQuery query;
    QString selectQuery = "select id, caption, text, image, cost, balance, state, flags from " + DB_GOALS_LIST_TABLE + " where login=\"" + login + "\" order by id;";

    if (query.exec(selectQuery)) {
        while (query.next()) {
            int id = query.value(query.record().indexOf("id")).toInt();
            QString caption = query.value(query.record().indexOf("caption")).toString();
            QString text = query.value(query.record().indexOf("text")).toString();

            QPixmap image;
            QByteArray imageData = query.value(query.record().indexOf("image")).toByteArray();
            image.loadFromData(imageData, "PNG");

            QString cost = query.value(query.record().indexOf("cost")).toString();
            QString balance = query.value(query.record().indexOf("balance")).toString();
            QString state = query.value(query.record().indexOf("state")).toString();
            QString flags = query.value(query.record().indexOf("flags")).toString();

            Goal *goal = (new Goal())->setId(id)->setCaption(caption)->setText(text)->setImage(image)
                    ->setCost(cost)->setBalance(balance)->setState(state)->setFlags(flags);

            goals.insert(id, *goal);
        }
    }
    else {
        qDebug() << DB_EXECUTE_QUERY_ERROR_MSG + selectQuery;
    }

    return goals;
}

QList<Income> Database::getIncomes(QString login, QDate fromDate, QDate toDate)
{
    QList<Income> incomes;

    QSqlQuery query;
    QString selectQuery = "select id, op_date, value, category, flags from " + DB_INCOME_TABLE +
            " where login=\"" + login + "\" and op_date between \"" +
            fromDate.toString(Operation::DATE_FORMAT) + "\" and \"" +
            toDate.toString(Operation::DATE_FORMAT) + "\" order by id;";

    if (query.exec(selectQuery)) {
        while (query.next()) {
            QDate date = query.value(query.record().indexOf("op_date")).toDate();
            QString value = query.value(query.record().indexOf("value")).toString();
            QString category = query.value(query.record().indexOf("category")).toString();

            incomes.append(Income(date, value, category));
        }
    }
    else {
        qDebug() << DB_EXECUTE_QUERY_ERROR_MSG + selectQuery;
    }

    return incomes;
}

QList<Consumption> Database::getConsumptions(QString login, QDate fromDate, QDate toDate)
{
    QList<Consumption> consumptions;

    QSqlQuery query;
    QString selectQuery = "select id, op_date, value, category, flags from " + DB_CONSUMPTION_TABLE +
            " where login=\"" + login + "\" and op_date between \"" +
            fromDate.toString(Operation::DATE_FORMAT) + "\" and \"" +
            toDate.toString(Operation::DATE_FORMAT) + "\" order by id;";

    if (query.exec(selectQuery)) {
        while (query.next()) {
            QDate date = query.value(query.record().indexOf("op_date")).toDate();
            QString value = query.value(query.record().indexOf("value")).toString();
            QString category = query.value(query.record().indexOf("category")).toString();

            consumptions.append(Consumption(date, value, category));
        }
    }
    else {
        qDebug() << DB_EXECUTE_QUERY_ERROR_MSG + selectQuery;
    }

    return consumptions;
}

QList<Piggybank> Database::getPiggybanks(QString login, QDate fromDate, QDate toDate)
{
    QList<Piggybank> piggybanks;

    QSqlQuery query;
    QString selectQuery = "select id, op_date, value, direction, flags from " + DB_PIGGYBANK_TABLE +
            " where login=\"" + login + "\" and op_date between \"" +
            fromDate.toString(Operation::DATE_FORMAT) + "\" and \"" +
            toDate.toString(Operation::DATE_FORMAT) + "\" order by id;";

    if (query.exec(selectQuery)) {
        while (query.next()) {
            QDate date = query.value(query.record().indexOf("op_date")).toDate();
            QString value = query.value(query.record().indexOf("value")).toString();
            QString direction = query.value(query.record().indexOf("direction")).toString();

            piggybanks.append(Piggybank(date, value, direction));
        }
    }
    else {
        qDebug() << DB_EXECUTE_QUERY_ERROR_MSG + selectQuery;
    }

    return piggybanks;
}

QList<Goals> Database::getGoals(QString login, QDate fromDate, QDate toDate)
{
    QList<Goals> goalsList;

    QSqlQuery query;
    QString selectQuery = "select id, op_date, value, goal_id, flags from " + DB_GOALS_TABLE +
            " where login=\"" + login + "\" and op_date between \"" +
            fromDate.toString(Operation::DATE_FORMAT) + "\" and \"" +
            toDate.toString(Operation::DATE_FORMAT) + "\" order by id;";

    if (query.exec(selectQuery)) {
        while (query.next()) {
            QDate date = query.value(query.record().indexOf("op_date")).toDate();
            QString value = query.value(query.record().indexOf("value")).toString();
            int goalId = query.value(query.record().indexOf("goal_id")).toInt();

            goalsList.append(Goals(date, value, goalId));
        }
    }
    else {
        qDebug() << DB_EXECUTE_QUERY_ERROR_MSG + selectQuery;
    }

    return goalsList;
}

QMap<QString, QString> Database::getConsumptionsByCategories(QString login)
{
    return getValuesByCategories(login, DB_CONSUMPTION_TABLE);
}

QMap<QString, QString> Database::getIncomesByCategories(QString login)
{
    return getValuesByCategories(login, DB_INCOME_TABLE);
}

QMap<QString, QString> Database::getValuesByCategories(QString login, QString table)
{
    QMap<QString, QString> valuesByCategories;
    QSqlQuery query;
    QString selectQuery = "select sum(value) as sumValue, category from " + table +
            " where login=\"" + login + "\" group by category;";

    if (query.exec(selectQuery)) {
        while (query.next()) {
            QString sumValue = query.value(query.record().indexOf("sumValue")).toString();
            QString category = query.value(query.record().indexOf("category")).toString();
            valuesByCategories.insert(category, sumValue);
        }
    }
    else {
        qDebug() << DB_EXECUTE_QUERY_ERROR_MSG + selectQuery;
    }

    return valuesByCategories;
}
