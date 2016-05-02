#include "changepasswordwindow.h"
#include "ui_changepasswordwindow.h"
#include "users.h"
#include "mainwindow.h"
#include "tablewindow.h"

ChangePasswordWindow::ChangePasswordWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePasswordWindow)
{
    ui->setupUi(this);
}

ChangePasswordWindow::ChangePasswordWindow(QWidget *parent, QString login) :
    QWidget(parent),
    ui(new Ui::ChangePasswordWindow)
{
    ui->setupUi(this);
    this->login = login;
}

ChangePasswordWindow::~ChangePasswordWindow()
{
    delete ui;
}

void ChangePasswordWindow::on_btnChange_clicked()
{
    Users *users = new Users();
    users->setUserPassword(login, ui->lePassword->text());

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    close();
}

void ChangePasswordWindow::on_btnClose_clicked()
{
    TableWindow *tableWindow = new TableWindow(0, login);
    tableWindow->Prepare("");
    tableWindow->show();
    close();
}
