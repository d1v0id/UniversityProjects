#ifndef SIGNINWINDOW_H
#define SIGNINWINDOW_H

#include "managementwindow.h"
#include <QMainWindow>

namespace Ui {
class SignInWindow;
}

class SignInWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SignInWindow(QWidget *parent = 0);
    ~SignInWindow();

private slots:
    void on_btn_clicked();
    void on_lbRescuePassword_linkActivated(const QString &link);
    void on_lbSignUp_linkActivated(const QString &link);

private:
    static const QString DIALOG_TITLE;
    static const QString DIALOG_WRONG_CREDENTIALS;
    static const QString DIALOG_WRONG_LOGIN;

    Ui::SignInWindow *ui;
    ManagementWindow *managementWindow;

    void rescuePassword(QString);
};

#endif // SIGNINWINDOW_H
