#include "player.h"

Player::Player(const QString& playerName)
    : m_name(playerName)
{
}

void Player::nextTurn()
{
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