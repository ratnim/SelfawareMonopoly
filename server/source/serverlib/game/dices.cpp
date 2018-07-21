#include "dices.h"

Dices::Dices(int d1, int d2)
    : first(d1)
    , second(d2)
{
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
