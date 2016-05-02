#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class TableWindow;
}

class TableWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TableWindow(QWidget *parent = 0);
    explicit TableWindow(QWidget *parent, QString login);
    ~TableWindow();
    void Prepare(QString filter);

private slots:
    void Connect();
    void Find();
    void ChangePassword();
    void AddNewUser();
    void CloseTableWindow();

private:
    Ui::TableWindow *ui;
    QString login;
};

#endif // TABLEWINDOW_H
