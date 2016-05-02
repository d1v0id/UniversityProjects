#include "templatesdialog.h"
#include "ui_templatesdialog.h"
#include "database.h"
#include <QMessageBox>

const QString TemplatesDialog::CONSUMPTION_TEMPLATES = "CONSUMPTION_TEMPLATE";
const QString TemplatesDialog::INCOME_TEMPLATES = "INCOME_TEMPLATE";

TemplatesDialog::TemplatesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TemplatesDialog)
{
    ui->setupUi(this);
    tableModel = new QStandardItemModel(0, 2, this);
    moneyValidator = new QDoubleValidator(0, 100, 2, this);

    tableModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Сумма")));
    tableModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Категория")));

    ui->tvTemplates->setModel(tableModel);
    ui->tvTemplates->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tvTemplates->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tvTemplates->horizontalHeader()->setStretchLastSection(true);
    ui->cbCategory->lineEdit()->setPlaceholderText("Категория");
    ui->leValue->setValidator(moneyValidator);
}

TemplatesDialog::~TemplatesDialog()
{
    delete ui;
}

void TemplatesDialog::on_btnCancel_clicked()
{
    reject();
}

bool TemplatesDialog::loadTemplates(User *user, QString type, QString value, QString category)
{
    QList<QStringList *> *templates;
    QStringList *categories;

    if (type.compare(CONSUMPTION_TEMPLATES) == 0) {
        setWindowTitle("Шаблоны расходов");
        templates = Database::getInstance().getConsumptionTemplates(user->getLogin());
        categories = Database::getInstance().getConsumptionCategories(user->getLogin());
    }
    else if (type.compare(INCOME_TEMPLATES) == 0) {
        setWindowTitle("Шаблоны доходов");
        templates = Database::getInstance().getIncomeTemplates(user->getLogin());
        categories = Database::getInstance().getIncomeCategories(user->getLogin());
    }
    else {
        return false;
    }

    this->user = user;
    this->type = type;
    tableModel->clear();
    tableModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Сумма")));
    tableModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Категория")));

    foreach (QStringList *templateItem, *templates) {
        QList<QStandardItem*> row;

        foreach (QString item, *templateItem) {
            QStandardItem *rowItem = new QStandardItem(item);
            row.append(rowItem);
        }

        tableModel->appendRow(row);
    }

    ui->cbCategory->clear();
    ui->cbCategory->addItem("");

    foreach (QString category, *categories) {
        ui->cbCategory->addItem(category);
    }

    ui->cbCategory->setCurrentText(category);
    ui->leValue->setText(value);

    delete templates;
    delete categories;

    return true;
}

void TemplatesDialog::on_btnAddConsumptionTemplate_clicked()
{
    QList<QStandardItem*> row;
    QStandardItem *rowItem;

    rowItem = new QStandardItem(ui->leValue->text());
    row.append(rowItem);

    rowItem = new QStandardItem(ui->cbCategory->lineEdit()->text());
    row.append(rowItem);

    tableModel->appendRow(row);
}

void TemplatesDialog::on_btnDeleteConsumptionTemplate_clicked()
{
    int rowIndex = ui->tvTemplates->currentIndex().row();
    tableModel->removeRow(rowIndex);
}

void TemplatesDialog::on_btnOK_clicked()
{
    int rowIndex = ui->tvTemplates->currentIndex().row();

    if (rowIndex >= 0) {
        this->templateValue = tableModel->data(tableModel->index(rowIndex, 0)).toString();
        this->templateCategory = tableModel->data(tableModel->index(rowIndex, 1)).toString();
    }

    QList<QStringList *> *templates = new QList<QStringList *>();

    for (int i = 0; i < tableModel->rowCount(); i++) {
        QStringList *item = new QStringList();
        item->append(tableModel->data(tableModel->index(i, 0)).toString());
        item->append(tableModel->data(tableModel->index(i, 1)).toString());
        templates->append(item);
    }

    bool result;

    if (this->type.compare(CONSUMPTION_TEMPLATES) == 0) {
        result = Database::getInstance().setConsumptionTemplates(user->getLogin(), templates);
    }
    else if (this->type.compare(INCOME_TEMPLATES) == 0) {
        result = Database::getInstance().setIncomeTemplates(user->getLogin(), templates);
    }

    if (result) {
        accept();
    }
    else {
        QMessageBox* pmbx = new QMessageBox("Шаблоны", "Ошибка при сохранении шаблонов!",
            QMessageBox::Warning, QMessageBox::Ok, 0, QMessageBox::Escape);

        pmbx->exec();
        delete pmbx;
    }

    delete templates;
}

QString TemplatesDialog::getTemplateValue()
{
    return templateValue;
}

QString TemplatesDialog::getTemplateCategory()
{
    return templateCategory;
}
