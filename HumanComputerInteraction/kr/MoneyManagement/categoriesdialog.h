#ifndef CATEGORIESDIALOG_H
#define CATEGORIESDIALOG_H

#include "user.h"
#include <QDialog>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QString>
#include <QTableView>

namespace Ui {
class CategoriesDialog;
}

class CategoriesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CategoriesDialog(QWidget *parent = 0);
    ~CategoriesDialog();
    bool loadCategories(User *user);

private slots:
    void on_btnOK_clicked();
    void on_btnCancel_clicked();
    void on_btnAddConsumptionCategory_clicked();
    void on_btnAddIncomeCategory_clicked();
    void on_btnEditConsumptionCategory_clicked();
    void on_btnEditIncomeCategory_clicked();
    void on_btnDeleteConsumptionCategory_clicked();
    void on_btnDeleteIncomeCategory_clicked();

private:
    static const int COLS_COUNT;
    static const QString CATEGORY_COLUMN_HEADER;
    static const QString CATEGORY_TITLE;
    static const QString CATEGORY_SET_CATEGORIES_ERROR_MSG;

    Ui::CategoriesDialog *ui;
    User *user;
    QStandardItemModel *consumptionTableModel;
    QStandardItemModel *incomeTableModel;

    void addCategory(QStandardItemModel *);
    void editCategory(QTableView *, QStandardItemModel *);
};

#endif // CATEGORIESDIALOG_H
