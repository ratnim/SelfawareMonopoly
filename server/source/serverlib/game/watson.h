#pragma once

#include <random>

#include <game/dices.h>

class Watson
{
public:
    void addResult(Dices dices);
    Dices roll();

protected:
    std::vector<Dices> m_results;
};
