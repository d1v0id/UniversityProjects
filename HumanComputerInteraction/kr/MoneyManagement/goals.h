#ifndef GOALS_H
#define GOALS_H

#include "operation.h"

class Goals : public Operation
{
public:
    Goals(QDate, QString, int);
    int getGoalId();

private:
    int goalId;
};

#endif // GOALS_H
