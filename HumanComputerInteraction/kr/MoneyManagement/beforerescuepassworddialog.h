#ifndef BEFORERESCUEPASSWORDDIALOG_H
#define BEFORERESCUEPASSWORDDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class BeforeRescuePasswordDialog;
}

class BeforeRescuePasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BeforeRescuePasswordDialog(QWidget *parent = 0);
    ~BeforeRescuePasswordDialog();
    QString getLogin();

private slots:
    void on_btnOk_clicked();

private:
    static const QString DIALOG_TITLE;
    static const QString DIALOG_EMPTY_LOGIN;

    Ui::BeforeRescuePasswordDialog *ui;
    QString login;
};

#endif // BEFORERESCUEPASSWORDDIALOG_H
