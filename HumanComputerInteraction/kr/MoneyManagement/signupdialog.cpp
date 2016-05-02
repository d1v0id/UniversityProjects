#include "signupdialog.h"
#include "ui_signupdialog.h"
#include "moneyutils.h"
#include "user.h"
#include "users.h"
#include <QMessageBox>

const QString SignUpDialog::DIALOG_TITLE = "Регистрация";
const QString SignUpDialog::DIALOG_INVALID_FIELDS_MSG = "Введены не все данные или данные некорректные!";
const QString SignUpDialog::DIALOG_USER_ALREADY_EXISTS_MSG = "Ошибка регистрации.<br>Возможно пользователь с таким логином уже существует.";

SignUpDialog::SignUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpDialog)
{
    ui->setupUi(this);

    ui->cbCurrency->addItem(MoneyUtils::RUB);
    ui->cbCurrency->addItem(MoneyUtils::USD);
}

SignUpDialog::~SignUpDialog()
{
    delete ui;
}

bool SignUpDialog::verify_fields_first_part()
{
    QString passwordAgain = ui->lePasswordAgain->text();

    login = ui->leLogin->text();
    password = ui->lePassword->text();
    question = ui->teQuestion->toPlainText();
    answer = ui->leAnswer->text();

    if (login.isEmpty() || !Users::isValidLoginLength(login) ||
        password.isEmpty() ||
        (password.compare(passwordAgain) != 0) ||
        question.isEmpty() ||
        answer.isEmpty()) {

        return false;
    }

    return true;
}

bool SignUpDialog::verify_fields_second_part()
{
    birthDate = ui->deBirthDate->date();
    name = ui->leName->text();
    secondName = ui->leSecondName->text();
    currency = ui->cbCurrency->itemText(ui->cbCurrency->currentIndex());
    sex = "";

    if (ui->cbMale->isChecked()) {
        sex = ui->cbMale->text();
    }
    else if (ui->cbFemale->isChecked()) {
        sex = ui->cbFemale->text();
    }

    if (name.isEmpty() ||
        secondName.isEmpty() ||
        sex.isEmpty() ||
        birthDate.isNull() || !birthDate.isValid() || //TODO it's correct?
        currency.isEmpty()) {

        return false;
    }

    return true;
}

void SignUpDialog::on_cbMale_clicked()
{
    ui->cbFemale->setChecked(false);
}

void SignUpDialog::on_cbFemale_clicked()
{
    ui->cbMale->setChecked(false);
}

void SignUpDialog::on_btnBack_clicked()
{
    switch (ui->swPages->currentIndex()) {
    case 0:
        reject();
        break;

    case 1:
        ui->swPages->setCurrentIndex(0);
        break;
    }
}

void SignUpDialog::on_btnNext_clicked()
{
    QMessageBox* message = new QMessageBox(DIALOG_TITLE, DIALOG_INVALID_FIELDS_MSG,
                                        QMessageBox::Warning, QMessageBox::Ok, 0, 0);

    switch (ui->swPages->currentIndex()) {
    case 0:
        if (verify_fields_first_part()) {
            ui->swPages->setCurrentIndex(1);
        }
        else {
            message->exec();
        }
        break;

    case 1:
        if (verify_fields_second_part()) {
            if (addUser()) {
                accept();
            }
        }
        else {
            message->exec();
        }
        break;
    }

    delete message;
}

bool SignUpDialog::addUser()
{
    User *user = (new User())->setLogin(login)->setPassword(password)->setQuestion(question)
            ->setAnswer(answer)->setName(name)->setSecondName(secondName)->setSex(sex)
            ->setBirthDate(birthDate)->setCurrency(currency);

    bool result = Users::addUser(user);

    if (!result) {
        QMessageBox *message = new QMessageBox(DIALOG_TITLE, DIALOG_USER_ALREADY_EXISTS_MSG,
                                           QMessageBox::Warning, QMessageBox::Ok, 0, 0);
        message->exec();
        delete message;
    }

    return result;
}
