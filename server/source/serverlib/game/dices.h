#pragma once

#include <cstdlib>
#include <random>

class Dices
{
public:
    Dices(int d1, int d2);
    Dices(int distance);
    Dices();

    bool isDouble() const;
    int sum() const;

    int first;
    int second;

protected:
    static int random();
};
