#ifndef RESCUEPASSWORDDIALOG_H
#define RESCUEPASSWORDDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class RescuePasswordDialog;
}

class RescuePasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RescuePasswordDialog(QWidget *parent = 0);
    explicit RescuePasswordDialog(QWidget *, QString);
    ~RescuePasswordDialog();
    QString getAnswer();

private slots:
    void on_btnOk_clicked();

private:
    static const QString DIALOG_TITLE;
    static const QString DIALOG_EMPTY_ANSWER;

    Ui::RescuePasswordDialog *ui;
    QString answer;
};

#endif // RESCUEPASSWORDDIALOG_H
