#ifndef STATISTICWINDOW_H
#define STATISTICWINDOW_H

#include <QMainWindow>
#include "user.h"

namespace Ui {
class StatisticWindow;
}

class StatisticWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StatisticWindow(QWidget *parent = 0);
    ~StatisticWindow();
    void setUser(User *user);
    void setType(QString);
    bool prepare();

private:
    Ui::StatisticWindow *ui;
};

#endif // STATISTICWINDOW_H
