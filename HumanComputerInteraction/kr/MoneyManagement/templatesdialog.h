#ifndef TEMPLATESDIALOG_H
#define TEMPLATESDIALOG_H

#include "user.h"
#include <QDialog>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QString>
#include <QTableView>

namespace Ui {
class TemplatesDialog;
}

class TemplatesDialog : public QDialog
{
    Q_OBJECT

public:
    static const QString CONSUMPTION_TEMPLATES;
    static const QString INCOME_TEMPLATES;

    explicit TemplatesDialog(QWidget *parent = 0);
    ~TemplatesDialog();
    bool loadTemplates(User *, QString, QString, QString);
    QString getTemplateValue();
    QString getTemplateCategory();

private slots:
    void on_btnCancel_clicked();
    void on_btnAddConsumptionTemplate_clicked();
    void on_btnDeleteConsumptionTemplate_clicked();

    void on_btnOK_clicked();

private:
    Ui::TemplatesDialog *ui;
    QStandardItemModel *tableModel;
    QDoubleValidator *moneyValidator;
    User *user;
    QString type;
    QString templateValue;
    QString templateCategory;
};

#endif // TEMPLATESDIALOG_H
