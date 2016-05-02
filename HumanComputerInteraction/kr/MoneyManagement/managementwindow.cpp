#include "managementwindow.h"
#include "ui_managementwindow.h"
#include "database.h"
#include "income.h"
#include "consumption.h"
#include "piggybank.h"
#include "goals.h"
#include "piechartwidget.h"
#include <QMessageBox>
#include <QStringList>
#include <QStringListModel>
#include <QtDebug>

const QString ManagementWindow::ROOT_DB_LOGIN = "root";
const QString ManagementWindow::ROOT_DB_PASSWORD = "Ut5sho#f_zoh$e8ooGh!3phieKeiphee";

const QString ManagementWindow::UI_CATEGORY_PLACEHOLDER_TEXT = "Категория";
const QString ManagementWindow::GOALS_LIST_PLACEHOLDER_TEXT = "Цель";
const int ManagementWindow::HISTORY_TABLE_COLS_COUNT = 4;
const QString ManagementWindow::DATE_COLUMN_HEADER = "Дата";
const QString ManagementWindow::VALUE_COLUMN_HEADER = "Сумма";
const QString ManagementWindow::CATEGORY_COLUMN_HEADER = "Категория";
const QString ManagementWindow::TYPE_COLUMN_HEADER = "Тип";
const QString ManagementWindow::INCOME_COLUMN_TYPE = "Доход";
const QString ManagementWindow::CONSUMPTION_COLUMN_TYPE = "Расход";
const QString ManagementWindow::PIGGYBANK_IN_COLUMN_TYPE = "В копилку";
const QString ManagementWindow::SEND_TO_GOALS_COLUMN_TYPE = "Перевод на Цель";

ManagementWindow::ManagementWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManagementWindow)
{
    ui->setupUi(this);
    statisticWindow = new StatisticWindow();
    categoriesDialog = new CategoriesDialog();
    goalsDialog = new GoalsDialog();
    templatesDialog = new TemplatesDialog();
    moneyValidator = new QDoubleValidator(0, 100, 2, this);
    historyTableModel = new QStandardItemModel(0, HISTORY_TABLE_COLS_COUNT, this);

    ui->tvHistory->setModel(historyTableModel);

    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(ui->actionGoals, SIGNAL(triggered(bool)), this, SLOT(show_goals()));
    connect(ui->actionCategories, SIGNAL(triggered(bool)), this, SLOT(show_categories()));
    connect(ui->actionConsumption, SIGNAL(triggered(bool)), this, SLOT(show_consumption_statistic()));
    connect(ui->actionIncome, SIGNAL(triggered(bool)), this, SLOT(show_income_statistic()));
    connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(show_about()));

    setupAppearance();
}

void ManagementWindow::setupAppearance()
{
    ui->cbConsumptionCategory->lineEdit()->setPlaceholderText(UI_CATEGORY_PLACEHOLDER_TEXT);
    ui->cbIncomeCategory->lineEdit()->setPlaceholderText(UI_CATEGORY_PLACEHOLDER_TEXT);

    ui->leConsumptionValue->setValidator(moneyValidator);
    ui->leIncomeValue->setValidator(moneyValidator);
    ui->lePiggyBankValue->setValidator(moneyValidator);
    ui->leToGoalValue->setValidator(moneyValidator);

    ui->deConsumptionDate->setDate(QDate::currentDate());
    ui->deIncomeDate->setDate(QDate::currentDate());
    ui->dePiggyBankDate->setDate(QDate::currentDate());
    ui->deToGoalDate->setDate(QDate::currentDate());
}

ManagementWindow::~ManagementWindow()
{
    Database::getInstance().close();

    delete statisticWindow;
    delete categoriesDialog;
    delete goalsDialog;
    delete templatesDialog;
    delete moneyValidator;
    delete ui;
}

void ManagementWindow::show_consumption_statistic()
{
    statisticWindow->setUser(user);
    statisticWindow->setType(PieChartWidget::CONSUMPTION);

    if (statisticWindow->prepare()) {
        statisticWindow->show();
    }
}

void ManagementWindow::show_income_statistic()
{
    statisticWindow->setUser(user);
    statisticWindow->setType(PieChartWidget::INCOME);

    if (statisticWindow->prepare()) {
        statisticWindow->show();
    }
}

void ManagementWindow::show_categories()
{
    if (categoriesDialog->loadCategories(user)) {
        if (categoriesDialog->exec() == QDialog::Accepted) {
            updateCategories();
        }
    }
}

void ManagementWindow::show_goals()
{
    if (goalsDialog->loadGoals(user)) {
        if (goalsDialog->exec() == QDialog::Accepted) {
            updateGoals();
        }
    }
}

void ManagementWindow::show_about()
{
    QMessageBox* pmbx = new QMessageBox(
                "О программе",
                "<b>Money Management</b> <i>- легкий способ управления финансами</i><br><br><u>(c) Дмитрий Коннов</u>",
                QMessageBox::Information,
                QMessageBox::Ok,
                0,
                QMessageBox::Escape);

    pmbx->exec();
    delete pmbx;
}

void ManagementWindow::setSignedUser(User *user)
{
    this->user = user;
    Database::getInstance().open(ROOT_DB_LOGIN, ROOT_DB_PASSWORD);

    updateUserDependentUIItems();
    updateDayCard();
    updateCategories();
    updateGoals();

    ui->deDateRangeTo->setDate(QDate::currentDate());
    updateHistory();
}

void ManagementWindow::updateUserDependentUIItems()
{
    QString currency = user->getCurrency();

    if (!currency.isEmpty()) { //TODO check enum with values contains that currency
        ui->lbConsumptionCurrency->setText(currency);
        ui->lbConsumptionValueCurrency->setText(currency);
        ui->lbIncomeCurrency->setText(currency);
        ui->lbIncomeValueCurrency->setText(currency);
        ui->lbPiggyBankCurrency->setText(currency);
        ui->lbPiggyBankValueCurrency->setText(currency);
        ui->lbToGoalValueCurrency->setText(currency);
        ui->lbWalletCurrency->setText(currency);
    }
}

void ManagementWindow::updateDayCard()
{
    QString piggybankValue = Database::getInstance().getPiggybankValue(user->getLogin());
    ui->lePiggyBank->setText(piggybankValue);

    QString walletValue = Database::getInstance().getWalletValue(user->getLogin());
    ui->leWallet->setText(walletValue);

    QString todayConsumption = Database::getInstance().getTodayConsumption(user->getLogin());
    ui->leConsumption->setText(todayConsumption);

    QString todayIncome = Database::getInstance().getTodayIncome(user->getLogin());
    ui->leIncome->setText(todayIncome);
}

void ManagementWindow::updateCategories()
{
    QStringList *categories = Database::getInstance().getConsumptionCategories(user->getLogin());
    ui->cbConsumptionCategory->clear();
    ui->cbConsumptionCategory->addItem("");

    foreach (QString category, *categories) {
        ui->cbConsumptionCategory->addItem(category);
    }

    categories = Database::getInstance().getIncomeCategories(user->getLogin());
    ui->cbIncomeCategory->clear();
    ui->cbIncomeCategory->addItem("");

    foreach (QString category, *categories) {
        ui->cbIncomeCategory->addItem(category);
    }
}

void ManagementWindow::updateGoals()
{
    this->goals = Database::getInstance().getGoals(user->getLogin());
    this->goalsIndexes = new QList<int>();

    QStringListModel *model = new QStringListModel(this);
    QMapIterator<int, Goal> it(goals);
    QStringList list;
    list.append(GOALS_LIST_PLACEHOLDER_TEXT);

    while (it.hasNext()) {
        it.next();
        Goal goal = it.value();

        if ((goal.getFlags().compare(Goal::REMOVE_FLAG) != 0) &&
                (goal.getState().compare(Goal::ACHIEVED) != 0)) {
            goalsIndexes->push_back(it.key());
            list.append(goal.getCaption());
        }
    }

    model->setStringList(list);
    ui->cbToGoalGoalValue->setModel(model);
}

void ManagementWindow::on_btnAddConsumption_clicked()
{
    QDate date = ui->deConsumptionDate->date();
    QString value = ui->leConsumptionValue->text();
    QString category = ui->cbConsumptionCategory->currentText();

    if (Database::getInstance().addConsumption(user->getLogin(), Consumption(date, value, category))) {
        updateHistory();
        updateDayCard();

        ui->leConsumptionValue->clear();
        ui->cbConsumptionCategory->lineEdit()->clear();
    }
}

void ManagementWindow::on_lbConsumptionCategoryTemplate_linkActivated(const QString &link)
{
    qDebug() << link;
    categoryTemplateActivate(TemplatesDialog::CONSUMPTION_TEMPLATES, ui->leConsumptionValue, ui->cbConsumptionCategory);
}

void ManagementWindow::on_lbIncomeCategoryTemplate_linkActivated(const QString &link)
{
    qDebug() << link;
    categoryTemplateActivate(TemplatesDialog::INCOME_TEMPLATES, ui->leIncomeValue, ui->cbIncomeCategory);
}

void ManagementWindow::categoryTemplateActivate(QString type, QLineEdit *lineEdit, QComboBox *comboBox)
{
    // If fields have some text, show text in new template fields panel
    // if templates table has template with value and category equals field's then select row with that template
    // then templates window closed by OK button show value and category from selected row in value and category fields

    if (templatesDialog->loadTemplates(user, type, lineEdit->text(), comboBox->lineEdit()->text())) {
        if (templatesDialog->exec() == QDialog::Accepted) {
            lineEdit->setText(templatesDialog->getTemplateValue());
            comboBox->setCurrentText(templatesDialog->getTemplateCategory());
        }
    }
}

void ManagementWindow::on_btnAddIncome_clicked()
{
    QDate date = ui->deIncomeDate->date();
    QString value = ui->leIncomeValue->text();
    QString category = ui->cbIncomeCategory->currentText();

    if (Database::getInstance().addIncome(user->getLogin(), Income(date, value, category))) {
        updateHistory();
        updateDayCard();

        ui->leIncomeValue->clear();
        ui->cbIncomeCategory->lineEdit()->clear();
    }
}

void ManagementWindow::on_btnAddPiggybank_clicked()
{
    QDate date = ui->dePiggyBankDate->date();
    QString value = ui->lePiggyBankValue->text();

    if (Database::getInstance().addPiggybank(user->getLogin(), Piggybank(date, value, Piggybank::IN))) {
        updateHistory();
        updateDayCard();

        ui->lePiggyBankValue->clear();
    }
}

void ManagementWindow::on_btnSendToGoal_clicked()
{
    QDate date = ui->deToGoalDate->date();
    QString value = ui->leToGoalValue->text();
    int currentGoalsListIndex = ui->cbToGoalGoalValue->currentIndex() - 1;
    int goalId = goalsIndexes->value(currentGoalsListIndex);

    if (Database::getInstance().sendToGoal(user->getLogin(), Goals(date, value, goalId))) {
        updateHistory();
        updateDayCard();

        ui->leToGoalValue->clear();
        ui->cbToGoalGoalValue->setCurrentIndex(0);
    }

    updateGoals();
}

void ManagementWindow::updateHistory()
{
    QDate fromDate = ui->deDateRangeFrom->date();
    QDate toDate = ui->deDateRangeTo->date();

    historyTableModel->clear();

    historyTableModel->setHorizontalHeaderItem(0, new QStandardItem(QString(DATE_COLUMN_HEADER)));
    historyTableModel->setHorizontalHeaderItem(1, new QStandardItem(QString(VALUE_COLUMN_HEADER)));
    historyTableModel->setHorizontalHeaderItem(2, new QStandardItem(QString(CATEGORY_COLUMN_HEADER)));
    historyTableModel->setHorizontalHeaderItem(3, new QStandardItem(QString(TYPE_COLUMN_HEADER)));

    QList<Income> incomes = Database::getInstance().getIncomes(user->getLogin(), fromDate, toDate);

    foreach (Income income, incomes) {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QString(income.getDate().toString(Operation::DATE_FORMAT))));
        items.append(new QStandardItem(QString(income.getValue())));
        items.append(new QStandardItem(QString(income.getCategory())));
        items.append(new QStandardItem(QString(INCOME_COLUMN_TYPE)));

        historyTableModel->appendRow(items);
    }

    QList<Consumption> consumptions = Database::getInstance().getConsumptions(user->getLogin(), fromDate, toDate);

    foreach (Consumption consumption, consumptions) {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QString(consumption.getDate().toString(Operation::DATE_FORMAT))));
        items.append(new QStandardItem(QString(consumption.getValue())));
        items.append(new QStandardItem(QString(consumption.getCategory())));
        items.append(new QStandardItem(QString(CONSUMPTION_COLUMN_TYPE)));

        historyTableModel->appendRow(items);
    }

    QList<Piggybank> piggybanks = Database::getInstance().getPiggybanks(user->getLogin(), fromDate, toDate);

    foreach (Piggybank piggybank, piggybanks) {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QString(piggybank.getDate().toString(Operation::DATE_FORMAT))));
        items.append(new QStandardItem(QString(piggybank.getValue())));
        items.append(new QStandardItem(QString("")));
        QString type;

        if (piggybank.getDirection().compare(Piggybank::IN) == 0) {
            type = PIGGYBANK_IN_COLUMN_TYPE;
        }

        items.append(new QStandardItem(QString(type)));

        historyTableModel->appendRow(items);
    }

    QList<Goals> goalsList = Database::getInstance().getGoals(user->getLogin(), fromDate, toDate);

    foreach (Goals goalTransaction, goalsList) {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QString(goalTransaction.getDate().toString(Operation::DATE_FORMAT))));
        items.append(new QStandardItem(QString(goalTransaction.getValue())));

        Goal goal = goals.value(goalTransaction.getGoalId());
        QString goalCaption = goal.getCaption();
        items.append(new QStandardItem(QString(goalCaption)));

        items.append(new QStandardItem(QString(SEND_TO_GOALS_COLUMN_TYPE)));

        historyTableModel->appendRow(items);
    }
}

void ManagementWindow::on_deDateRangeFrom_dateChanged(const QDate &date)
{
    updateHistory();
}

void ManagementWindow::on_deDateRangeTo_dateChanged(const QDate &date)
{
    updateHistory();
}
