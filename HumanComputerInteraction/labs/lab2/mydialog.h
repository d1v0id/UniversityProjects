#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QSpinBox>
#include <QTextEdit>

class MyDialog: public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = 0);

private:
    QSpinBox *sBox;
    QTextEdit *tEdit;
    QComboBox *cBox;

private slots:
    void Wrf();
};

#endif // MYDIALOG_H

