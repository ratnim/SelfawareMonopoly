#pragma once

#include <cstdlib>
#include <random>

struct Dices
{
    Dices(int d1 = random(), int d2 = random());

    bool isDouble() const;
    int sum() const;

    const int first;
    const int second;

protected:
    static int random();
};
