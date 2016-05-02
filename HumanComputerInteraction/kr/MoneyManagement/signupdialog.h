#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>
#include <QString>
#include <QDate>

namespace Ui {
class SignUpDialog;
}

class SignUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignUpDialog(QWidget *parent = 0);
    ~SignUpDialog();

private slots:
    void on_cbMale_clicked();
    void on_cbFemale_clicked();
    void on_btnBack_clicked();
    void on_btnNext_clicked();

private:
    static const QString DIALOG_TITLE;
    static const QString DIALOG_INVALID_FIELDS_MSG;
    static const QString DIALOG_USER_ALREADY_EXISTS_MSG;

    Ui::SignUpDialog *ui;
    QDate birthDate;
    QString login;
    QString password;
    QString question;
    QString answer;
    QString name;
    QString secondName;
    QString currency;
    QString sex;

    bool verify_fields_first_part();
    bool verify_fields_second_part();
    bool addUser();
};

#endif // SIGNUPDIALOG_H
