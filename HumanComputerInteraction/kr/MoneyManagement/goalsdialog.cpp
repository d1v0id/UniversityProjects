#include "goalsdialog.h"
#include "ui_goalsdialog.h"
#include "database.h"
#include <QPixmap>
#include <QMessageBox>
#include <QStringListModel>
#include <QStringList>
#include <QMapIterator>
#include <QFileDialog>
#include <QtDebug>

const QString GoalsDialog::BACK_TEXT = "Назад";
const QString GoalsDialog::SAVE_TEXT = "Сохранить";
const QString GoalsDialog::CANCEL_TEXT = "Cancel";
const QString GoalsDialog::OK_TEXT = "OK";
const QString GoalsDialog::APPLY_TEXT = "Применить";
const QString GoalsDialog::EMPTY_GOAL_IMAGE_PIXMAP = "sad_cow.ico";
const QString GoalsDialog::DIALOG_TITLE = "Цели";
const QString GoalsDialog::DIALOG_SAVE_GOAL_ERROR = "Введены некорректные данные!";
const QString GoalsDialog::COST_TEXT = "Стоимость: ";
const QString GoalsDialog::BALANCE_TEXT = "Баланс: ";

GoalsDialog::GoalsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GoalsDialog)
{
    ui->setupUi(this);

    goalsListModel = new QStringListModel(this);
    ui->lvGoals->setModel(goalsListModel);
    ui->lbGoalImage->setScaledContents(true);
    ui->lbImage->setScaledContents(true);

    connect(ui->lvGoals->selectionModel(), SIGNAL(currentChanged(const QModelIndex &, const QModelIndex &)), this,
            SLOT(goalsList_currentRowChanged(const QModelIndex &, const QModelIndex &)));
}

GoalsDialog::~GoalsDialog()
{
    delete moneyValidator;
    delete ui;
}

void GoalsDialog::initUI()
{
    this->currentState = SHOW;
    this->moneyValidator = new QDoubleValidator(0, 100, 2, this);
    this->currentGoalId = Goal::NEW_GOAL_ID;

    ui->lbGoalImage->setPixmap(QPixmap(EMPTY_GOAL_IMAGE_PIXMAP));
    ui->leGoalCost->setValidator(moneyValidator);
    ui->btnDone->setText(OK_TEXT);
}

bool GoalsDialog::loadGoals(User *user)
{
    this->user = user;
    this->goals = Database::getInstance().getGoals(user->getLogin());
    this->goalsChanged = false;
    this->newGoalIdCounter = -2;

    initUI();
    updateGoalsList();

    return true;
}

void GoalsDialog::updateGoalsList()
{
    this->goalsIndexes = new QList<int>();

    QMapIterator<int, Goal> it(goals);
    QStringList list;

    while (it.hasNext()) {
        it.next();
        Goal goal = it.value();

        if (goal.getFlags().compare(Goal::REMOVE_FLAG) != 0) {
            goalsIndexes->push_back(it.key());
            list.append(goal.getCaption());
        }
    }

    this->goalsListModel->setStringList(list);

    ui->cbCompleted->setText("Недостигнута");
    ui->cbCompleted->setChecked(false);
    ui->lbImage->setPixmap(QPixmap(EMPTY_GOAL_IMAGE_PIXMAP));
    ui->lbCost->setText(COST_TEXT);
    ui->lbMoneyBalance->setText(BALANCE_TEXT);
}

void GoalsDialog::on_btnBack_clicked()
{
    switch (currentState) {
    case SHOW:
        reject();
        break;

    case EDIT:
        switchToShowState();
        break;
    }
}

void GoalsDialog::on_btnDone_clicked()
{
    switch (currentState) {
    case SHOW:
        if (goalsChanged) {
            Database::getInstance().setGoals(user->getLogin(), goals);
        }

        accept();
        break;

    case EDIT:
        if (saveGoalModifications()) {
            updateGoalsList();
            switchToShowState();
            setGoalsChanged();
        }
        break;
    }
}

void GoalsDialog::on_btnAddGoal_clicked()
{
    currentGoalId = Goal::NEW_GOAL_ID;
    switchToEditState();
}

void GoalsDialog::on_btnEditGoal_clicked()
{
    int currentIndex = ui->lvGoals->currentIndex().row();

    if (currentIndex >= 0) {
        currentGoalId = goalsIndexes->at(currentIndex);

        Goal goal = goals.value(currentGoalId);

        ui->leGoalCaption->setText(goal.getCaption());
        ui->teGoalText->setText(goal.getText());

        QPixmap image = goal.getImage();
        ui->lbGoalImage->setPixmap(image);

        ui->leGoalCost->setText(goal.getCost());

        switchToEditState();
    }
}

void GoalsDialog::on_btnRemoveGoal_clicked()
{
    int currentIndex = ui->lvGoals->currentIndex().row();

    if (currentIndex >= 0) {
        int currentGoalIndex = goalsIndexes->at(currentIndex);

        goals[currentGoalIndex].setFlags(Goal::REMOVE_FLAG);
        updateGoalsList();
        setGoalsChanged();
    }
}

void GoalsDialog::on_btnGoalLoadImage_clicked()
{
    QString imageFileName = QFileDialog::getOpenFileName(this,
        tr("Select Image File"), ".", tr("Image Files (*.jpg *.jpeg *.png *.bmp *.ico)"));

    ui->lbGoalImage->setPixmap(QPixmap(imageFileName));
}

void GoalsDialog::switchToEditState()
{
    currentState = EDIT;
    ui->btnBack->setText(BACK_TEXT);
    ui->btnDone->setText(SAVE_TEXT);
    ui->swPages->setCurrentIndex(1);
}

void GoalsDialog::switchToShowState()
{
    currentState = SHOW;
    ui->btnBack->setText(CANCEL_TEXT);
    ui->btnDone->setText(APPLY_TEXT);
    ui->swPages->setCurrentIndex(0);

    ui->leGoalCaption->clear();
    ui->teGoalText->clear();
    ui->leGoalCost->clear();
    ui->lbGoalImage->setPixmap(QPixmap(EMPTY_GOAL_IMAGE_PIXMAP));
}

bool GoalsDialog::saveGoalModifications()
{
    bool successfull = false;
    QString caption = ui->leGoalCaption->text();
    QString text = ui->teGoalText->toPlainText();
    QString cost = ui->leGoalCost->text();
    const QPixmap *image = ui->lbGoalImage->pixmap();

    if (!caption.isEmpty() && !text.isEmpty() && !cost.isEmpty()) {
        Goal *goal = (new Goal())->setCaption(caption)->setText(text)->setImage(*image)->setCost(cost);

        if (currentGoalId == Goal::NEW_GOAL_ID) {
            int newGoalId = generateNewGoalId();
            goal = goal->setId(newGoalId)->setBalance("0.00")->setState(Goal::NOT_ACHIEVED);
            goals.insert(newGoalId, *goal);
            goalsIndexes->push_back(newGoalId);
        }
        else {
            Goal bkpGoal = goals.value(currentGoalId);
            goal = goal->setId(currentGoalId)->setBalance(bkpGoal.getBalance())
                    ->setState(bkpGoal.getState());

            goals[currentGoalId] = *goal;
        }

        successfull = true;
    }
    else {
        QMessageBox *message = new QMessageBox(DIALOG_TITLE, DIALOG_SAVE_GOAL_ERROR,
                                           QMessageBox::Warning, QMessageBox::Ok, 0, 0);
        message->exec();
        delete message;
    }

    return successfull;
}

void GoalsDialog::setGoalsChanged()
{
    goalsChanged = true;
    ui->btnDone->setText(APPLY_TEXT);
}

int GoalsDialog::generateNewGoalId()
{
    return newGoalIdCounter--;
}

void GoalsDialog::goalsList_currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    int selectedIndex = current.row();
    int previousIndex = previous.row();

    if ((selectedIndex >= 0) && (selectedIndex != previousIndex)) {
        int currentGoalIndex = goalsIndexes->at(selectedIndex);
        Goal goal = goals.value(currentGoalIndex);

        if (goal.getState().compare(Goal::ACHIEVED) == 0) {
            ui->cbCompleted->setText("Достигнута");
            ui->cbCompleted->setChecked(true);
        }
        else {
            ui->cbCompleted->setText("Недостигнута");
            ui->cbCompleted->setChecked(false);
        }

        QPixmap image = goal.getImage();
        ui->lbImage->setPixmap(image);

        ui->lbCost->setText(COST_TEXT + goal.getCost());
        ui->lbMoneyBalance->setText(BALANCE_TEXT + goal.getBalance());
    }
}
