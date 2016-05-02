#include "goal.h"

const QString Goal::ACHIEVED = "ACHIEVED";
const QString Goal::NOT_ACHIEVED = "NOT_ACHIEVED";
const int Goal::NEW_GOAL_ID = -1;
const QString Goal::REMOVE_FLAG = "R";

Goal::Goal()
{
}

Goal *Goal::setId(int id)
{
    this->id = id;
    return this;
}

Goal *Goal::setCaption(QString caption)
{
    this->caption = caption;
    return this;
}

Goal *Goal::setText(QString text)
{
    this->text = text;
    return this;
}

Goal *Goal::setImage(QPixmap image)
{
    this->image = image;
    return this;
}

Goal *Goal::setCost(QString cost)
{
    this->cost = cost;
    return this;
}

Goal *Goal::setBalance(QString balance)
{
    this->balance = balance;
    return this;
}

Goal *Goal::setState(QString state)
{
    this->state = state;
    return this;
}

Goal *Goal::setFlags(QString flags)
{
    this->flags = flags;
    return this;
}

int Goal::getId()
{
    return id;
}

QString Goal::getCaption()
{
    return caption;
}

QString Goal::getText()
{
    return text;
}

QPixmap Goal::getImage()
{
    return image;
}

QString Goal::getCost()
{
    return cost;
}

QString Goal::getBalance()
{
    return balance;
}

QString Goal::getState()
{
    return state;
}

QString Goal::getFlags()
{
    return flags;
}
