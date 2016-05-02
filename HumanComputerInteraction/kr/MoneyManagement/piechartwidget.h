#ifndef PIECHARTWIDGET_H
#define PIECHARTWIDGET_H

#include <QWidget>
#include "user.h"

class PieChartWidget : public QWidget
{
    Q_OBJECT
public:
    static const QString CONSUMPTION;
    static const QString INCOME;

    explicit PieChartWidget(QWidget *parent = 0);
    void setStatisticUser(User *user);
    void setStatisticType(QString);
    bool prepare();

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:

private:
    static const int HIGH_COLOR_PART;
    static const int LOW_COLOR_PART;

    QList<QColor> pieColors;
    QList<double> pieChartData;
    QList<QString> dataCategories;

    User *user;
    QString type;
};

#endif // PIECHARTWIDGET_H
