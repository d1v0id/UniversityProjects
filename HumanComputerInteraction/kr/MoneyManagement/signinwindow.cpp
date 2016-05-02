#include "signinwindow.h"
#include "ui_signinwindow.h"
#include "beforerescuepassworddialog.h"
#include "rescuepassworddialog.h"
#include "signupdialog.h"
#include "changepassworddialog.h"
#include "users.h"
#include <QString>
#include <QDebug>
#include <QMessageBox>

const QString SignInWindow::DIALOG_TITLE = "Вход";
const QString SignInWindow::DIALOG_WRONG_CREDENTIALS = "Неверный логин или пароль!";
const QString SignInWindow::DIALOG_WRONG_LOGIN = "Неверный логин!";

SignInWindow::SignInWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SignInWindow)
{
    ui->setupUi(this);
    managementWindow = new ManagementWindow();

    connect(ui->lePassword, SIGNAL(returnPressed()), this, SLOT(on_btn_clicked()));
}

SignInWindow::~SignInWindow()
{
    delete managementWindow;
    delete ui;
}

void SignInWindow::on_btn_clicked()
{
    User *user = Users::getUser(ui->leLogin->text());

    if ((user != NULL) && (user->getPassword().compare(ui->lePassword->text()) == 0)) {
        close();
        managementWindow->setSignedUser(user);
        managementWindow->show();
    }
    else {
        QMessageBox *message = new QMessageBox(DIALOG_TITLE, DIALOG_WRONG_CREDENTIALS,
                                           QMessageBox::Warning, QMessageBox::Ok, 0, 0);
        message->exec();
        delete message;
    }
}

void SignInWindow::on_lbRescuePassword_linkActivated(const QString &link)
{
    qDebug() << link;
    QString login = ui->leLogin->text();

    if (login.isEmpty()) {
        BeforeRescuePasswordDialog *beforeRescuePasswordDialog = new BeforeRescuePasswordDialog();
        if (beforeRescuePasswordDialog->exec() == QDialog::Accepted) {
            login = beforeRescuePasswordDialog->getLogin();
            rescuePassword(login);
        }
    }
    else {
        rescuePassword(login);
    }
}

void SignInWindow::on_lbSignUp_linkActivated(const QString &link)
{
    qDebug() << link;
    SignUpDialog *signUpDialog = new SignUpDialog();
    signUpDialog->exec();

    delete signUpDialog;
}

void SignInWindow::rescuePassword(QString login)
{
    User *user = Users::getUser(login);

    if (user != NULL) {
        RescuePasswordDialog *rescuePasswordDialog = new RescuePasswordDialog(0, user->getQuestion());

        if (rescuePasswordDialog->exec() == QDialog::Accepted) {
            if (rescuePasswordDialog->getAnswer().compare(user->getAnswer()) == 0) {
                ChangePasswordDialog *changePasswordDialog = new ChangePasswordDialog();

                if (changePasswordDialog->exec() == QDialog::Accepted) {
                    Users::setUserPassword(login, changePasswordDialog->getPassword());
                }

                delete changePasswordDialog;
            }
        }

        delete rescuePasswordDialog;
    }
    else {
        QMessageBox *message = new QMessageBox(DIALOG_TITLE, DIALOG_WRONG_LOGIN,
                                           QMessageBox::Warning, QMessageBox::Ok, 0, 0);
        message->exec();
        delete message;
    }
}
