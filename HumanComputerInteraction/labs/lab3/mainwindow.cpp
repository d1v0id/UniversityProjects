#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QtDebug>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(autosave()));
    timer->start(10000);

    QTimer::singleShot(20000, this, SLOT(expired()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_text_clicked()
{
    fName = QFileDialog::getOpenFileName(0, "Open File", "", "*.txt");
    QFile file(fName);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->label->setText(fName);
        QTextStream in(&file);
        //in.setCodec("UTF-8");
        ui->textEdit->setText(in.readAll());
        file.close();
    }
    else {
        qDebug() << "Ошибка открытия файла" << endl;
    }
}

void MainWindow::on_save_text_clicked()
{
    if (fName == "") {
        fName = QFileDialog::getSaveFileName(0, "Save File", "", "*.txt");
    }
    QFile file(fName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        ui->label->setText(fName);
        QTextStream out(&file);
        //out.setCodec("UTF-8");
        out << ui->textEdit-> toPlainText();
        file.close();
    }
    else {
        qDebug() << "Ошибка открытия файла" << endl;
    }
}

void MainWindow::on_clear_text_clicked()
{
    ui->textEdit->clear();
}

void MainWindow::on_exit_text_clicked()
{
    QMessageBox *mBox = new QMessageBox(
                "Выход",
                "Сохранить изменения?",
                QMessageBox::Question,
                QMessageBox::Yes,
                QMessageBox::No,
                QMessageBox::Cancel | QMessageBox::Escape);

    switch (mBox->exec()) {
    case QMessageBox::Yes:
        on_save_text_clicked();

    case QMessageBox::No:
        close();

    case QMessageBox::Cancel:
        return;
    }
}

void MainWindow::autosave()
{
    if (fName != "") {
        QFile file(fName + "_temp");

        // if (file.exists()) ???

        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            //out.setCodec("UTF-8");
            out << ui->textEdit-> toPlainText();
            file.close();
        }
        else {
            qDebug() << "Ошибка открытия файла" << endl;
        }

        /*QMessageBox *mBox = new QMessageBox(
                "Автосохранение",
                "Произведено автосохранение в файл " + fName + "_temp",
                QMessageBox::Information,
                QMessageBox::Ok, 0, 0);

        mBox->exec();*/
    }
}

void MainWindow::expired()
{
    QMessageBox *mBox = new QMessageBox;
    mBox->setText("Истек пробный период программы :(");
    mBox->setStandardButtons(QMessageBox::Ok);
    mBox->setIconPixmap(QPixmap(":/cow_money_icon.jpg"));
    mBox->exec();
    close();
}
