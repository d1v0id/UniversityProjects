#ifndef RESQUEPASSWDWINDOW_H
#define RESQUEPASSWDWINDOW_H

#include <QWidget>
#include <QString>

namespace Ui {
class ResquePasswdWindow;
}

static const QString RESCUE_PASSWD_CAPTION = "Ваш пароль";
static const QString RESCUE_WRONG_PASSWD_CAPTION = "Неверно";
static const QString RESCUE_WRONG_PASSWD_MSG = "Неправильный ответ!";

class ResquePasswdWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ResquePasswdWindow(QWidget *parent = 0);
    explicit ResquePasswdWindow(QWidget *parent, QString login);
    ~ResquePasswdWindow();

private slots:
    void on_btnConfirm_clicked();

private:
    Ui::ResquePasswdWindow *ui;
    QString login;
    QString right_answer;
    QString right_passwd;
};

#endif // RESQUEPASSWDWINDOW_H
