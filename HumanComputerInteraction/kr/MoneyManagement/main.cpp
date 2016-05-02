#include "signinwindow.h"
#include "database.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Because addDatabase is not thread safe
    QSqlDatabase db = QSqlDatabase::addDatabase(Database::DB_TYPE);
    Database::getInstance().initilizeDatabase(db);

    SignInWindow signInWindow;
    signInWindow.setFixedSize(signInWindow.size());
    signInWindow.show();

    return app.exec();
}
