#include "rescuepassworddialog.h"
#include "ui_rescuepassworddialog.h"
#include <QMessageBox>

const QString RescuePasswordDialog::DIALOG_TITLE = "Восстановление пароля";
const QString RescuePasswordDialog::DIALOG_EMPTY_ANSWER = "Пустой ответ!";

RescuePasswordDialog::RescuePasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RescuePasswordDialog)
{
    ui->setupUi(this);
}

RescuePasswordDialog::RescuePasswordDialog(QWidget *parent, QString question) :
    QDialog(parent),
    ui(new Ui::RescuePasswordDialog)
{
    ui->setupUi(this);
    ui->teQuestion->setText(question);
}

RescuePasswordDialog::~RescuePasswordDialog()
{
    delete ui;
}

void RescuePasswordDialog::on_btnOk_clicked()
{
    if (ui->leAnswer->text().isEmpty()) {
        QMessageBox *message = new QMessageBox(DIALOG_TITLE, DIALOG_EMPTY_ANSWER,
                                           QMessageBox::Warning, QMessageBox::Ok, 0, 0);
        message->exec();
        delete message;
    }
    else {
        answer = ui->leAnswer->text();
        accept();
    }
}

QString RescuePasswordDialog::getAnswer()
{
    return answer;
}
