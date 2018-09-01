#pragma once

#include <cstdlib>
#include <random>

class Dices
{
public:
    Dices(int d1 = random(), int d2 = random());

    bool isDouble() const;
    int sum() const;

    int first;
    int second;

protected:
    static int random();
};
