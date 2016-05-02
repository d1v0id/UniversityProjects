#include "resquepasswdwindow.h"
#include "ui_resquepasswdwindow.h"
#include "users.h"
#include "simplecrypt.h"
#include <QString>
#include <QStringList>
#include <QMessageBox>

ResquePasswdWindow::ResquePasswdWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResquePasswdWindow)
{
    ui->setupUi(this);
}

ResquePasswdWindow::ResquePasswdWindow(QWidget *parent, QString login) :
    QWidget(parent),
    ui(new Ui::ResquePasswdWindow)
{
    ui->setupUi(this);

    Users *users = new Users();
    QStringList userData = users->getUserData(login);

    if (!userData.empty()) {
        this->right_passwd = userData.value(0);
        this->right_answer = userData.value(2);
        ui->lblQuestion->setText(ui->lblQuestion->text() + " " + userData.value(1));
    }
}

ResquePasswdWindow::~ResquePasswdWindow()
{
    delete ui;
}

void ResquePasswdWindow::on_btnConfirm_clicked()
{
    QString caption;
    QString text;

    if (ui->edAnswer->text().compare(this->right_answer) == 0) {
        caption = RESCUE_PASSWD_CAPTION;
        text = this->right_passwd;
    }
    else {
        caption = RESCUE_WRONG_PASSWD_CAPTION;
        text = RESCUE_WRONG_PASSWD_MSG;
    }

    QMessageBox* mbx = new QMessageBox(caption, text, QMessageBox::Information, QMessageBox::Ok, 0, 0);
    mbx->exec();
    delete mbx;
}
