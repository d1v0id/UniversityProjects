#include "mainwindow.h"
#include "database.h"
#include <QApplication>
#include <QtGui>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlError>
#include <QtSql>
#include <QTableView>
#include <QSqlTableModel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Database::getInstance().Create("lab4", "Ut5sho#f_zoh$e8ooGh!3phieKeiphee");

    MainWindow w;
    w.show();

    // в главном меню:
    // смена пользователя
    // поиск по базе
    // смена пароля
    // создание нового пользователя (доступно только admin)

    return a.exec();
}
