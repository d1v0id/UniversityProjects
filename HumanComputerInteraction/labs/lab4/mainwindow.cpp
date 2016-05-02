#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "users.h"
#include "resquepasswdwindow.h"
#include "tablewindow.h"
#include "simplecrypt.h"
#include <QMessageBox>
#include <QTableView>
#include <QSqlTableModel>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_resquePasswd_linkActivated(const QString &link)
{
    qDebug() << link;
    QString login = ui->leLogin->text();

    if (!login.isEmpty()) {
        ResquePasswdWindow *rpw = new ResquePasswdWindow(0, login);
        rpw->show();
    }
    else {
        QMessageBox *mbx = new QMessageBox(
            "Восстановление пароля",
            "Сначала введите логин в текущем окне.",
            QMessageBox::Warning,
            QMessageBox::Ok,
            0,
            0);
        mbx->exec();
        delete mbx;
    }
}

void MainWindow::on_btnConnect_clicked()
{
    QString login = ui->leLogin->text();
    QString passwd = ui->lePasswd->text();

    Users *users = new Users();
    bool valid = users->validate(login, passwd);

    if (valid) {
        TableWindow *tblWindow = new TableWindow(0, login);
        tblWindow->Prepare("");
        tblWindow->show();
        this->close();
        //this->hide();
    }
}
