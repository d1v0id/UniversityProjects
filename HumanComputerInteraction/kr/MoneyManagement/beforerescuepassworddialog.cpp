#include "beforerescuepassworddialog.h"
#include "ui_beforerescuepassworddialog.h"
#include <QMessageBox>

const QString BeforeRescuePasswordDialog::DIALOG_TITLE = "Восстановление пароля";
const QString BeforeRescuePasswordDialog::DIALOG_EMPTY_LOGIN = "Пустой логин!";

BeforeRescuePasswordDialog::BeforeRescuePasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BeforeRescuePasswordDialog)
{
    ui->setupUi(this);
}

BeforeRescuePasswordDialog::~BeforeRescuePasswordDialog()
{
    delete ui;
}

void BeforeRescuePasswordDialog::on_btnOk_clicked()
{
    if (ui->leLogin->text().isEmpty()) {
        QMessageBox *message = new QMessageBox(DIALOG_TITLE, DIALOG_EMPTY_LOGIN,
                                           QMessageBox::Warning, QMessageBox::Ok, 0, 0);
        message->exec();
        delete message;
    }
    else {
        login = ui->leLogin->text();
        accept();
    }
}

QString BeforeRescuePasswordDialog::getLogin()
{
    return login;
}
