#include "dices.h"

bool Dices::isDouble() const
{
    return first == second;
}

int Dices::sum() const
{
    return first + second;
}
