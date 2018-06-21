#pragma once

#include <cstdlib>

struct Dices
{
    const int first = (std::rand() % 6) + 1;
    const int second = (std::rand() % 6) + 1;
    bool isDouble() const;
    int sum() const;
};
