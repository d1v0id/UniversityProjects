#ifndef MANAGEMENTWINDOW_H
#define MANAGEMENTWINDOW_H

#include "statisticwindow.h"
#include "categoriesdialog.h"
#include "goalsdialog.h"
#include "templatesdialog.h"
#include "user.h"
#include "goal.h"
#include <QMainWindow>
#include <QString>
#include <QDoubleValidator>
#include <QMap>
#include <QStandardItemModel>
#include <QComboBox>

namespace Ui {
class ManagementWindow;
}

class ManagementWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManagementWindow(QWidget *parent = 0);
    ~ManagementWindow();
    void setSignedUser(User *);

private slots:
    void show_consumption_statistic();
    void show_income_statistic();
    void show_categories();
    void show_goals();
    void show_about();
    void on_btnAddConsumption_clicked();
    void on_btnAddIncome_clicked();
    void on_btnAddPiggybank_clicked();
    void on_btnSendToGoal_clicked();
    void on_lbConsumptionCategoryTemplate_linkActivated(const QString &link);
    void on_lbIncomeCategoryTemplate_linkActivated(const QString &link);

    void on_deDateRangeFrom_dateChanged(const QDate &date);

    void on_deDateRangeTo_dateChanged(const QDate &date);

private:
    static const QString ROOT_DB_LOGIN;
    static const QString ROOT_DB_PASSWORD;

    static const QString UI_CATEGORY_PLACEHOLDER_TEXT;
    static const QString GOALS_LIST_PLACEHOLDER_TEXT;
    static const int HISTORY_TABLE_COLS_COUNT;
    static const QString DATE_COLUMN_HEADER;
    static const QString VALUE_COLUMN_HEADER;
    static const QString CATEGORY_COLUMN_HEADER;
    static const QString TYPE_COLUMN_HEADER;
    static const QString INCOME_COLUMN_TYPE;
    static const QString CONSUMPTION_COLUMN_TYPE;
    static const QString PIGGYBANK_IN_COLUMN_TYPE;
    static const QString SEND_TO_GOALS_COLUMN_TYPE;

    Ui::ManagementWindow *ui;
    StatisticWindow *statisticWindow;
    CategoriesDialog *categoriesDialog;
    GoalsDialog *goalsDialog;
    TemplatesDialog *templatesDialog;
    User *user;
    QDoubleValidator *moneyValidator;
    QMap<int, Goal> goals;
    QList<int> *goalsIndexes;
    QStandardItemModel *historyTableModel;

    void setupAppearance();
    void updateUserDependentUIItems();
    void updateDayCard();
    void updateCategories();
    void updateGoals();
    void updateHistory();
    void categoryTemplateActivate(QString, QLineEdit *, QComboBox *);
};

#endif // MANAGEMENTWINDOW_H
