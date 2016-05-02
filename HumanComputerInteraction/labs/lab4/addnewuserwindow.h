#ifndef ADDNEWUSERWINDOW_H
#define ADDNEWUSERWINDOW_H

#include <QWidget>

namespace Ui {
class AddNewUserWindow;
}

class AddNewUserWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AddNewUserWindow(QWidget *parent = 0);
    ~AddNewUserWindow();

private slots:
    void on_btnAdd_clicked();
    void on_btnClose_clicked();

private:
    Ui::AddNewUserWindow *ui;
};

#endif // ADDNEWUSERWINDOW_H
