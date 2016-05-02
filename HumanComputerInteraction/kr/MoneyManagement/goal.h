#ifndef GOAL_H
#define GOAL_H

#include <QString>
#include <QPixmap>

class Goal
{
public:
    static const QString ACHIEVED;
    static const QString NOT_ACHIEVED;
    static const int NEW_GOAL_ID;
    static const QString REMOVE_FLAG;

    Goal();
    Goal *setId(int);
    Goal *setCaption(QString);
    Goal *setText(QString);
    Goal *setImage(QPixmap);
    Goal *setCost(QString);
    Goal *setBalance(QString);
    Goal *setState(QString);
    Goal *setFlags(QString);
    int getId();
    QString getCaption();
    QString getText();
    QPixmap getImage();
    QString getCost();
    QString getBalance();
    QString getState();
    QString getFlags();

private:
    int id;
    QString caption;
    QString text;
    QPixmap image;
    QString cost;
    QString balance;
    QString state;
    QString flags;
};

#endif // GOAL_H
