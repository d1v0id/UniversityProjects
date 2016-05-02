#include "statisticwindow.h"
#include "ui_statisticwindow.h"

StatisticWindow::StatisticWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StatisticWindow)
{
    ui->setupUi(this);
}

StatisticWindow::~StatisticWindow()
{
    delete ui;
}

void StatisticWindow::setUser(User *user)
{
    ui->wdgConsumptionsAndIncomes->setStatisticUser(user);
}

void StatisticWindow::setType(QString type)
{
    ui->wdgConsumptionsAndIncomes->setStatisticType(type);
}

bool StatisticWindow::prepare()
{
    return ui->wdgConsumptionsAndIncomes->prepare();
}
