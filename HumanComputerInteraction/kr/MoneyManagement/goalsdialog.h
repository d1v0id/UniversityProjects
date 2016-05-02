#ifndef GOALSDIALOG_H
#define GOALSDIALOG_H

#include "user.h"
#include "goal.h"
#include <QDialog>
#include <QString>
#include <QDoubleValidator>
#include <QMap>
#include <QModelIndex>
#include <QStringListModel>

enum State { SHOW, EDIT };

namespace Ui {
class GoalsDialog;
}

class GoalsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GoalsDialog(QWidget *parent = 0);
    ~GoalsDialog();
    bool loadGoals(User *user);
    
private slots:
    void on_btnBack_clicked();
    void on_btnDone_clicked();
    void on_btnAddGoal_clicked();
    void on_btnEditGoal_clicked();
    void on_btnRemoveGoal_clicked();
    void on_btnGoalLoadImage_clicked();
    void goalsList_currentRowChanged(const QModelIndex &, const QModelIndex &);

private:
    static const QString BACK_TEXT;
    static const QString SAVE_TEXT;
    static const QString CANCEL_TEXT;
    static const QString OK_TEXT;
    static const QString APPLY_TEXT;
    static const QString EMPTY_GOAL_IMAGE_PIXMAP;
    static const QString DIALOG_TITLE;
    static const QString DIALOG_SAVE_GOAL_ERROR;
    static const QString COST_TEXT;
    static const QString BALANCE_TEXT;

    Ui::GoalsDialog *ui;
    QStringListModel *goalsListModel;
    User *user;
    State currentState;
    QDoubleValidator *moneyValidator;
    int currentGoalId;
    QMap<int, Goal> goals;
    QList<int> *goalsIndexes;
    bool goalsChanged;
    int newGoalIdCounter;

    void initUI();
    void updateGoalsList();
    void switchToEditState();
    void switchToShowState();
    bool saveGoalModifications();
    void setGoalsChanged();
    int generateNewGoalId();
};

#endif // GOALSDIALOG_H
