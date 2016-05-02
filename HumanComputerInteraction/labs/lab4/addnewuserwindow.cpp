#include "addnewuserwindow.h"
#include "ui_addnewuserwindow.h"
#include "mainwindow.h"
#include "users.h"
#include <QMessageBox>

AddNewUserWindow::AddNewUserWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddNewUserWindow)
{
    ui->setupUi(this);
}

AddNewUserWindow::~AddNewUserWindow()
{
    delete ui;
}

void AddNewUserWindow::on_btnAdd_clicked()
{
    if (ui->lePassword->text().compare(ui->lePasswordAgain->text()) == 0) {
        Users *users = new Users();
        bool successfull =  users->addUserData(ui->leLogin->text(), ui->lePassword->text(), ui->leQuestion->text(), ui->leAnswer->text());
        delete users;

        if (!successfull) {
            QMessageBox *mbx = new QMessageBox(
                "Добавление пользователя",
                "Пользователь с таким логином уже существует.",
                QMessageBox::Warning,
                QMessageBox::Ok,
                0,
                0);
            mbx->exec();
            delete mbx;
            return;
        }

        close();
    }
    else {
        QMessageBox *mbx = new QMessageBox(
            "Добавление пользователя",
            "Введенные пароли не совпадают.",
            QMessageBox::Warning,
            QMessageBox::Ok,
            0,
            0);
        mbx->exec();
        delete mbx;
    }
}

void AddNewUserWindow::on_btnClose_clicked()
{
    close();
}
