#include "dices.h"

#include <utils/exception.h>

Dices::Dices()
    : first(random())
    , second(random())
{
}

Dices::Dices(int d1, int d2)
    : first(d1)
    , second(d2)
{
}

Dices::Dices(int distance)
{
    if (distance < 2 || distance > 12)
    {
        throw Exception("Distance not reachable with two dices", Error::InternalError);
    }

    if (distance > 7)
    {
        first = 6;
    }
    else
    {
        first = 1;
    }

    second = distance - first;
}

bool Dices::isDouble() const
{
    return first == second;
}

int Dices::sum() const
{
    return first + second;
}

int Dices::random()
{
    static std::random_device realRandomDevice;
    static std::mt19937 randomDevice(realRandomDevice());
    static std::uniform_int_distribution<> distribution(1, 6);

    return distribution(randomDevice);
}
