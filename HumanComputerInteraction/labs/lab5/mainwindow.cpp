#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "moneymanagementxmlparser.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QDate>
#include <QDomDocument>
#include <QDomElement>
#include <QXmlInputSource>
#include <QXmlSimpleReader>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tempFilePathLabel->setVisible(false);
    ui->tempFileSaveProgressBar->setVisible(false);
    ui->tempFileSaveLabel->setVisible(false);

    ui->tempFileSaveProgressBar->setValue(0);
    ui->readXMLProgressBar->setValue(0);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(autosave()));
    //timer->start(10000);
    timer->start(180000);
}

MainWindow::~MainWindow()
{
    if (!fName.isEmpty()) {
        QString tmpFile = fName + TEMP_FILE_POSTFIX;
        QFile::remove(tmpFile);
    }

    delete ui;
}

void MainWindow::on_btnExit_clicked()
{
    close();
}

void MainWindow::on_btnSave_clicked()
{
    if (fName.isEmpty()) {
        fName = QFileDialog::getSaveFileName(0, "Save File", "", "*.xml");
    }
    saveFile();
}

void MainWindow::on_btnSaveAs_clicked()
{
    fName = QFileDialog::getSaveFileName(0, "Save File As", "", "*.*");
    saveFile();
}

void MainWindow::saveFile()
{
    QFile file(fName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        ui->sourcePathLabel->setText(fName);
        QTextStream out(&file);
        //out.setCodec("UTF-8");
        out << ui->textEdit->toPlainText();
        file.close();

        setUpdateAvailability(true);
    }
    else {
        qDebug() << "Ошибка открытия файла" << endl;
    }
}

void MainWindow::on_btnOpen_clicked()
{
    fName = QFileDialog::getOpenFileName(0, "Open File", "", "*.xml");
    QFile file(fName);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->sourcePathLabel->setText(fName);
        QTextStream in(&file);
        //in.setCodec("UTF-8");
        ui->textEdit->setText(in.readAll());
        file.close();

        setUpdateAvailability(true);
    }
    else {
        qDebug() << "Ошибка открытия файла" << endl;
    }
}

void MainWindow::on_btnClear_clicked()
{
    ui->textEdit->clear();
}

void MainWindow::autosave()
{
    QString tempFile;
    if (!fName.isEmpty()) {
        tempFile = fName + TEMP_FILE_POSTFIX;
    }
    else {
        tempFile = TEMP_PATH + QDate::currentDate().toString().replace(" ", "");
    }

    QFile file(tempFile);

    // if (file.exists()) ???

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        ui->tempFilePathLabel->setVisible(true);
        ui->tempFileSaveProgressBar->setVisible(true);
        ui->tempFileSaveLabel->setVisible(true);

        ui->tempFilePathLabel->setText(tempFile);
        QTextStream out(&file);
        //out.setCodec("UTF-8");
        QString text = ui->textEdit->toPlainText();
        int progressStep = (text.length() > 0) ? (100 / text.length()) : 100;

        for (int i = 0; i < text.length(); i++) {
            int progressValue = progressStep * (i + 1);
            ui->tempFileSaveProgressBar->setValue(progressValue);
            ui->tempFileSaveLabel->setText(QString::number(progressValue) + "%");
            out << text[i];
        }

        ui->tempFileSaveProgressBar->setValue(0);
        ui->tempFileSaveLabel->setText("0%");

        ui->tempFilePathLabel->setVisible(false);
        ui->tempFileSaveProgressBar->setVisible(false);
        ui->tempFileSaveLabel->setVisible(false);
        file.close();

        setUpdateAvailability(true);
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

void MainWindow::setUpdateAvailability(bool availability)
{
    ui->btnUpdate->setEnabled(availability);
}

void MainWindow::on_textEdit_textChanged()
{
    setUpdateAvailability(false);
}

void MainWindow::on_cbDOM_clicked()
{
    ui->cbSAX->setChecked(false);
}

void MainWindow::on_cbSAX_clicked()
{
    ui->cbDOM->setChecked(false);
}

void MainWindow::on_btnUpdate_clicked()
{
    ui->treeWidget->clear();

    if (ui->cbDOM->isChecked()) {
        QDomDocument domDoc;
        QFile file(fName);


        if (file.open(QIODevice::ReadOnly)) {
            if (domDoc.setContent(&file)) {
                QTreeWidgetItem *treeRootItem = new QTreeWidgetItem();

                QDomElement domElement = domDoc.documentElement();
                traverseNode(domElement, *treeRootItem);
            }

            file.close();
        }
    }
    else if (ui->cbSAX->isChecked()) {
        MoneyManagementXMLParser *handler = new MoneyManagementXMLParser(ui->treeWidget);
        QFile file(fName);
        QXmlInputSource source(&file);
        QXmlSimpleReader reader;

        reader.setContentHandler(handler);
        reader.parse(source);

        //QTreeWidgetItem *treeRootItem = handler->getTreeRootItem();

        file.close();
    }
}

void MainWindow::traverseNode(const QDomNode &node, QTreeWidgetItem &treeRootItem)
{
    QTreeWidgetItem *treeRootItem1;
    QDomNode domNode = node.firstChild();
    while (!domNode.isNull()) {
        if (domNode.isElement()) {
            QDomElement domElement = domNode.toElement();

            if (!domElement.isNull()) {
                if (domElement.tagName().compare("person") == 0) {
                    treeRootItem1 = new QTreeWidgetItem(ui->treeWidget);
                    treeRootItem1->setText(0, "Persion ID");
                    treeRootItem1->setText(1, domElement.attribute("id", ""));

                    qDebug() << "Persion ID: " << domElement.attribute("id", "");
                }
                else {
                    QTreeWidgetItem *treeItem = new QTreeWidgetItem();
                    treeItem->setText(0, domElement.tagName());
                    treeItem->setText(1, domElement.text());
                    treeRootItem.addChild(treeItem);

                    qDebug() << "TagName: " << domElement.tagName() << "\tText: " << domElement.text();
                }
            }
        }

        traverseNode(domNode, *treeRootItem1);
        domNode = domNode.nextSibling();
    }
}
