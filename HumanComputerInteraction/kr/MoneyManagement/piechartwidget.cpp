#include "piechartwidget.h"
#include "database.h"
#include "moneyutils.h"
#include <QPainter>
#include <QPoint>
#include <QString>
#include <QtDebug>
#include <QMap>

const QString PieChartWidget::CONSUMPTION = "CONSUMPTION";
const QString PieChartWidget::INCOME = "INCOME";

const int PieChartWidget::HIGH_COLOR_PART = 216;
const int PieChartWidget::LOW_COLOR_PART = 128;

PieChartWidget::PieChartWidget(QWidget *parent) : QWidget(parent)
{
}

void PieChartWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRectF size = QRectF(10, 10, this->width() - 10, this->width() - 10);

    painter.setPen(Qt::black);
    QString caption;
    if (type.compare(CONSUMPTION) == 0) {
       caption = "Расходы";
    }
    else if (type.compare(INCOME) == 0) {
       caption = "Доходы";
    }

    painter.drawText(QPoint(0, 10), caption);

    long summ = 0;
    for (int i = 0; i < pieChartData.size(); i++) {
        summ += pieChartData.at(i);
    }

    int start = 0;
    for (int i = 0; i < pieChartData.size() - 1; i++) {
        painter.setBrush(pieColors[i]);
        //qDebug() << pieChartData.size();
        long value = (pieChartData.at(i) * 360) / summ;
        //qDebug() << pieChartData.at(i);
        painter.drawPie(size, start * 16, value * 16);
        start += value;
    }

    painter.setBrush(pieColors[pieChartData.size() - 1]);
    painter.drawPie(size, start * 16, (360 - start) * 16);
    painter.setBrush(Qt::white);

    painter.drawRect(QRectF(0, this->width() + 5, this->width() - 5, 20 * pieChartData.size()));
    for (int i = 0; i < pieChartData.size(); i++) {
        painter.setBrush(pieColors[i]);
        painter.drawRect(QRectF(0, this->width() + (20 * i) + 5, 20, 20));

        painter.setPen(Qt::black);
        painter.drawText(QPoint(30, this->width() + (20 * i) + 20), dataCategories[i]);
    }
}

void PieChartWidget::setStatisticUser(User *user)
{
    this->user = user;
}

void PieChartWidget::setStatisticType(QString type)
{
    this->type = type;
}

bool PieChartWidget::prepare()
{
    QMap<QString, QString> valuesByCategories;

    if (type.compare(CONSUMPTION) == 0) {
        valuesByCategories = Database::getInstance().getConsumptionsByCategories(user->getLogin());
    }
    else if (type.compare(INCOME) == 0) {
        valuesByCategories = Database::getInstance().getIncomesByCategories(user->getLogin());
    }
    else {
        return false;
    }

    qsrand(qrand());

    pieChartData.clear();
    dataCategories.clear();
    pieColors.clear();

    foreach (QString category, valuesByCategories.keys()) {
        pieChartData.append(valuesByCategories.value(category).toDouble());
        dataCategories.append(category);

        QColor color;
        do {
            color = QColor(qrand() % ((HIGH_COLOR_PART + 1) - LOW_COLOR_PART) + LOW_COLOR_PART,
                           qrand() % ((HIGH_COLOR_PART + 1) - LOW_COLOR_PART) + LOW_COLOR_PART,
                           qrand() % ((HIGH_COLOR_PART + 1) - LOW_COLOR_PART) + LOW_COLOR_PART);
        } while (pieColors.contains(color));

        pieColors.append(color);
    }

    return true;
}
