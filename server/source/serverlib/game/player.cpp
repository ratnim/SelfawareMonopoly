#include "player.h"

Player::Player(const QString& playerName)
    : m_name(playerName)
{
}

void Player::nextTurn()
{
    m_timesRolled = 0;
    m_canRoll = true;

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
    m_canRoll = false;
}

bool Player::canRoll() const
{
    return m_canRoll;
}

void Player::canRoll(bool value)
{
	m_canRoll = value;
}

bool Player::operator==(const Player& other) const
{
    return m_name == other.name();
}
