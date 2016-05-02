#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"
#include <QTextCharFormat>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->action->connect(ui->action, SIGNAL(triggered()), this, SLOT(About_Lab1()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->calendarWidget->setFirstDayOfWeek(Qt::DayOfWeek(index));
    QTextCharFormat format;
    format.setForeground(qvariant_cast<QColor>("green"));
    ui->calendarWidget->setWeekdayTextFormat(Qt::DayOfWeek(index), format);

    for (int i = 0; i < 7; i++) {
        if (i != index) {
            QTextCharFormat format1;
            format1.setForeground(qvariant_cast<QColor>("black"));
            ui->calendarWidget->setWeekdayTextFormat(Qt::DayOfWeek(i), format1);
        }
    }

    //QTextCharFormat format1 = ui->calendarWidget->weekdayTextFormat(index + 1));

    //qDebug() << color << endl;
}

void MainWindow::About_Lab1()
{
    About *about = new About();
    about->show();
}
