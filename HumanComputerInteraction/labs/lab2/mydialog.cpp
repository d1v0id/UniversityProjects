#include "mydialog.h"
#include <QHBoxLayout>
#include <QStringList>
#include <QPushButton>
#include <QFile>
#include <QFileDialog>
#include <QIODevice>
#include <QDebug>

MyDialog:: MyDialog(QWidget *parent): QDialog(parent)
{
    setWindowTitle("Анкета");

    sBox = new QSpinBox;
    tEdit = new QTextEdit;
    cBox = new QComboBox;

    QHBoxLayout *Hlay = new QHBoxLayout;
    QPushButton *pButton = new QPushButton("Сохранить");
    QStringList items;

    items << "Первое" << "Второе" << "Третье";
    cBox->addItems(items);
    QObject::connect(pButton, SIGNAL(clicked(bool)), this, SLOT(Wrf()));

    Hlay->addWidget(sBox);
    Hlay->addWidget(tEdit);
    Hlay->addWidget(cBox);
    Hlay->addWidget(pButton);
    this->setLayout(Hlay);
}

void MyDialog::Wrf()
{
    QString fName = QFileDialog::getSaveFileName(0, "Сохранить", "", "*.txt");
    QFile file(fName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << sBox->value() << endl;
        out << tEdit->toPlainText() << endl;
        out << cBox->currentText() << endl;
        file.close();
    }
    else {
        qDebug() << "Ошибка сохрания в файл." << endl;
    }
}
