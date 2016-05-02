#include "goals.h"

Goals::Goals(QDate date, QString value, int goalId) : Operation(date, value)
{
    this->goalId = goalId;
}

int Goals::getGoalId()
{
    return goalId;
}
