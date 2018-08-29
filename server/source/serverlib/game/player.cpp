#include "player.h"

Player::Player(const QString& playerName)
    : m_name(playerName)
{
}

void Player::nextTurn()
{
    m_timesRolled = 0;

    if (m_jailTurns > 0)
        --m_jailTurns;
}

bool Player::inJail() const
{
    return m_jailTurns > 0;
}

void Player::jail()
{
    m_jailTurns = 3;
}

void Player::leaveJail()
{
    m_jailTurns = 0;
}

int Player::position() const
{
    return m_position;
}

const QString& Player::name() const
{
    return m_name;
}

void Player::move(int distance)
{
    m_position += distance;
}

void Player::moveTo(int fieldIndex)
{
    m_position = fieldIndex;
}

int Player::timesRolled() const
{
    return m_timesRolled;
}

void Player::rolled()
{
    ++m_timesRolled;
}
