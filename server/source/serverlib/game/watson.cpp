#include "watson.h"

void Watson::addResult(Dices dices)
{
    m_results.push_back(dices);
}

Dices Watson::roll()
{
    if (m_results.empty())
    {
        return Dices();
    }

    auto dices = m_results.back();
    m_results.pop_back();
    return dices;
}
