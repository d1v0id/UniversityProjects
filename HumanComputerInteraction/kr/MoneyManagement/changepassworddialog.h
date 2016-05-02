#ifndef CHANGEPASSWORDDIALOG_H
#define CHANGEPASSWORDDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class ChangePasswordDialog;
}

class ChangePasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePasswordDialog(QWidget *parent = 0);
    ~ChangePasswordDialog();
    QString getPassword();

private slots:
    void on_btnOK_clicked();

private:
    static const QString DIALOG_TITLE;
    static const QString DIALOG_WRONG_PASSWORD;

    Ui::ChangePasswordDialog *ui;
    QString password;
};

#endif // CHANGEPASSWORDDIALOG_H
