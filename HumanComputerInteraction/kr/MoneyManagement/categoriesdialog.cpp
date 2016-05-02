#include "categoriesdialog.h"
#include "ui_categoriesdialog.h"
#include "database.h"
#include <QStringList>
#include <QInputDialog>
#include <QMessageBox>

const int CategoriesDialog::COLS_COUNT = 1;
const QString CategoriesDialog::CATEGORY_COLUMN_HEADER = "Категория";
const QString CategoriesDialog::CATEGORY_TITLE = "Категории";
const QString CategoriesDialog::CATEGORY_SET_CATEGORIES_ERROR_MSG = "Ошибка при сохранении категорий!";

CategoriesDialog::CategoriesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CategoriesDialog)
{
    ui->setupUi(this);
    consumptionTableModel = new QStandardItemModel(0, COLS_COUNT, this);
    incomeTableModel = new QStandardItemModel(0, COLS_COUNT, this);

    consumptionTableModel->setHorizontalHeaderItem(0, new QStandardItem(QString(CATEGORY_COLUMN_HEADER)));
    incomeTableModel->setHorizontalHeaderItem(0, new QStandardItem(QString(CATEGORY_COLUMN_HEADER)));

    ui->tvConsumptionCategories->setModel(consumptionTableModel);
    ui->tvIncomeCategories->setModel(incomeTableModel);

    ui->tvConsumptionCategories->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tvIncomeCategories->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

CategoriesDialog::~CategoriesDialog()
{
    delete ui;
}

bool CategoriesDialog::loadCategories(User *user)
{
    this->user = user;

    consumptionTableModel->clear();
    incomeTableModel->clear();

    consumptionTableModel->setHorizontalHeaderItem(0, new QStandardItem(QString(CATEGORY_COLUMN_HEADER)));
    incomeTableModel->setHorizontalHeaderItem(0, new QStandardItem(QString(CATEGORY_COLUMN_HEADER)));

    QStringList *categories = Database::getInstance().getConsumptionCategories(user->getLogin());
    int i = 0;

    foreach (QString category, *categories) {
        QStandardItem *row = new QStandardItem(QString(category));
        consumptionTableModel->setItem(i++, row);
    }

    categories = Database::getInstance().getIncomeCategories(user->getLogin());
    i = 0;

    foreach (QString category, *categories) {
        QStandardItem *row = new QStandardItem(QString(category));
        incomeTableModel->setItem(i++, row);
    }

    delete categories;
    return true;
}

void CategoriesDialog::on_btnOK_clicked()
{
    QStringList *consumptionCategories = new QStringList();
    QStringList *incomeCategories = new QStringList();

    for (int i = 0; i < consumptionTableModel->rowCount(); i++) {
        QString item = consumptionTableModel->item(i)->text();
        consumptionCategories->append(item);
    }

    for (int i = 0; i < incomeTableModel->rowCount(); i++) {
        QString item = incomeTableModel->item(i)->text();
        incomeCategories->append(item);
    }

    if (Database::getInstance().setConsumptionCategories(user->getLogin(), consumptionCategories) &&
            Database::getInstance().setIncomeCategories(user->getLogin(), incomeCategories)) {

        accept();
    }
    else {
        QMessageBox* pmbx = new QMessageBox(CATEGORY_TITLE, CATEGORY_SET_CATEGORIES_ERROR_MSG,
            QMessageBox::Warning, QMessageBox::Ok, 0, QMessageBox::Escape);

        pmbx->exec();
        delete pmbx;
    }

    delete consumptionCategories;
    delete incomeCategories;
}

void CategoriesDialog::on_btnAddConsumptionCategory_clicked()
{
    addCategory(consumptionTableModel);
}

void CategoriesDialog::on_btnAddIncomeCategory_clicked()
{
    addCategory(incomeTableModel);
}

void CategoriesDialog::addCategory(QStandardItemModel *model)
{
    bool ok;
    QString text = QInputDialog::getText(this, CATEGORY_COLUMN_HEADER, "", QLineEdit::Normal, "", &ok);

    if (ok && !text.isEmpty()) {
        QStandardItem *row = new QStandardItem(text);
        model->setItem(model->rowCount(), row);
    }
}

void CategoriesDialog::on_btnEditConsumptionCategory_clicked()
{
    editCategory(ui->tvConsumptionCategories, consumptionTableModel);
}

void CategoriesDialog::on_btnEditIncomeCategory_clicked()
{
    editCategory(ui->tvIncomeCategories, incomeTableModel);
}

void CategoriesDialog::editCategory(QTableView *tableView, QStandardItemModel *model)
{
    bool ok;
    int rowIndex = tableView->currentIndex().row();

    if (rowIndex >= 0) {
        QString value = tableView->currentIndex().data().toString();
        QString text = QInputDialog::getText(this, CATEGORY_COLUMN_HEADER, "", QLineEdit::Normal, value, &ok);

        if (ok && !text.isEmpty()) {
            QStandardItem *row = new QStandardItem(text);
            model->setItem(rowIndex, row);
        }
    }
}

void CategoriesDialog::on_btnDeleteConsumptionCategory_clicked()
{
    int rowIndex = ui->tvConsumptionCategories->currentIndex().row();
    consumptionTableModel->removeRow(rowIndex);
}

void CategoriesDialog::on_btnDeleteIncomeCategory_clicked()
{
    int rowIndex = ui->tvIncomeCategories->currentIndex().row();
    incomeTableModel->removeRow(rowIndex);
}

void CategoriesDialog::on_btnCancel_clicked()
{
    reject();
}
