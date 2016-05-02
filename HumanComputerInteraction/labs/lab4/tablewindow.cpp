#include "tablewindow.h"
#include "ui_tablewindow.h"
#include "database.h"
#include "users.h"
#include "mainwindow.h"
#include "changepasswordwindow.h"
#include "addnewuserwindow.h"
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QInputDialog>
#include <QtDebug>

TableWindow::TableWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TableWindow)
{
    ui->setupUi(this);
}

TableWindow::TableWindow(QWidget *parent, QString login) :
    QMainWindow(parent),
    ui(new Ui::TableWindow)
{
    ui->setupUi(this);
    this->login = login;

    ui->actionConnect->connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(Connect()));
    ui->actionFind->connect(ui->actionFind, SIGNAL(triggered()), this, SLOT(Find()));
    ui->actionChange_password->connect(ui->actionChange_password, SIGNAL(triggered()), this, SLOT(ChangePassword()));
    ui->actionAdd_new_user->connect(ui->actionAdd_new_user, SIGNAL(triggered()), this, SLOT(AddNewUser()));
    ui->actionExit->connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(CloseTableWindow()));

    Users *user = new Users();
    ui->actionAdd_new_user->setVisible(user->userCanEdit(login));
}

TableWindow::~TableWindow()
{
    delete ui;
}

void TableWindow::Prepare(QString filter)
{
    Database database = Database::getInstance();
    QSqlDatabase db = database.getDatabase();

    if (db.open()) {
        Users *user = new Users();
        if (user->userCanEdit(login)) {
            QSqlTableModel *model = new QSqlTableModel();
            model->setTable("money_management");
            model->setFilter(filter);
            model->select();
            model->setEditStrategy(QSqlTableModel::OnFieldChange);
            ui->tableView->setModel(model);
        }
        else {
            QSqlQueryModel *model = new QSqlQueryModel();
            QString query = "select * from money_management";

            if (!filter.isEmpty()) {
                query +=  " where " + filter;
            }

            model->setQuery(query, db);
            ui->tableView->setModel(model);
        }
    }
    else {
        qDebug() << "Open db error.";
    }
}

void TableWindow::Connect()
{
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    close();
}

void TableWindow::Find()
{
    bool bOk;
    QString name = QInputDialog::getText(0, "Поиск", "Name", QLineEdit::Normal, "", &bOk);

    if (bOk) {
        Prepare("name like '%" + name + "%'");
    }
}

void TableWindow::ChangePassword()
{
    ChangePasswordWindow *changePasswordWindow = new ChangePasswordWindow(0, login);
    changePasswordWindow->show();

    Database database = Database::getInstance();
    QSqlDatabase db = database.getDatabase();
    db.close();
    close();
}

void TableWindow::AddNewUser()
{
    AddNewUserWindow *addNewUserWindow = new AddNewUserWindow();
    addNewUserWindow->show();

    /*Database database = Database::getInstance();
    QSqlDatabase db = database.getDatabase();
    db.close();
    close();*/
}

void TableWindow::CloseTableWindow()
{
    Database database = Database::getInstance();
    QSqlDatabase db = database.getDatabase();
    db.close();
    exit(0);
}
