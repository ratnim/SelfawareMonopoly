#include "enter.h"

Enter::Enter(Player& player)
    : State(player)
{
}

void Enter::ready(bool ready)
{
    m_ready = ready;
}

bool Enter::isReady() const
{
    return m_ready;
}
