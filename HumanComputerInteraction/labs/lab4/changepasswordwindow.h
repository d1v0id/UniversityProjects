#ifndef CHANGEPASSWORDWINDOW_H
#define CHANGEPASSWORDWINDOW_H

#include <QWidget>
#include <QString>

namespace Ui {
class ChangePasswordWindow;
}

class ChangePasswordWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePasswordWindow(QWidget *parent = 0);
    explicit ChangePasswordWindow(QWidget *parent, QString login);
    ~ChangePasswordWindow();

private slots:
    void on_btnChange_clicked();

    void on_btnClose_clicked();

private:
    Ui::ChangePasswordWindow *ui;
    QString login;
};

#endif // CHANGEPASSWORDWINDOW_H
