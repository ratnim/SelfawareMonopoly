#include "jail.h"

#include <utils/exception.h>

void Jail::jail()
{
    m_jailed = true;
    m_turns = 2;
}

bool Jail::inJail()
{
    return m_jailed;
}

bool Jail::needToPay()
{
    if (m_jailed)
		return m_turns <= 0;

	return false;
}

bool Jail::escape(const Dices& dices)
{
    if (m_jailed == false)
        throw Exception("Internal Error: Player is not in jail.", Exception::InternalError);

	if (dices.isDouble())
	{
        m_jailed = false;
        return true;
	}

	return false;
}

void Jail::nextTurn()
{
    if (m_jailed)
        --m_turns;
}
