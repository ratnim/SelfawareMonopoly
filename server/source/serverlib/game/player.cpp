#include "player.h"

void Player::nextTurn()
{
    m_jail.nextTurn();
    canRoll = true;
    rolled = 0;
}

Jail& Player::jail()
{
    return m_jail;
}
