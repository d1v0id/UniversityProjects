#include "changepassworddialog.h"
#include "ui_changepassworddialog.h"
#include <QMessageBox>

const QString ChangePasswordDialog::DIALOG_TITLE = "Изменить пароль";
const QString ChangePasswordDialog::DIALOG_WRONG_PASSWORD = "Пароли не совпадают или один из них пустой!";

ChangePasswordDialog::ChangePasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePasswordDialog)
{
    ui->setupUi(this);
}

ChangePasswordDialog::~ChangePasswordDialog()
{
    delete ui;
}

void ChangePasswordDialog::on_btnOK_clicked()
{
    if (!ui->lePassword->text().isEmpty() &&
            (ui->lePassword->text().compare(ui->lePasswordAgain->text()) == 0)) {

        password = ui->lePassword->text();
        accept();
    }
    else {
        QMessageBox *message = new QMessageBox(DIALOG_TITLE, DIALOG_WRONG_PASSWORD,
                                           QMessageBox::Warning, QMessageBox::Ok, 0, 0);
        message->exec();
        delete message;
    }
}

QString ChangePasswordDialog::getPassword()
{
    return password;
}
