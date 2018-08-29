#include "bank.h"

#include <utils/exception.h>

void Bank::createAccount(const QString& name, int deposit)
{
	if (m_accounts.find(name) != m_accounts.end())
	{
        throw new Exception("Bank account already exists.", Error::InternalError);
	}

	m_accounts.emplace(name, 0);
}

void Bank::transferMoney(const QString& reciever, int amount)
{

}

int Bank::balance(const QString& name) const
{
    auto& it = m_accounts.find(name);
    if (it == m_accounts.end())
    {
        throw new Exception("Bank account does not exists.", Error::InternalError);
    }

	return it->second;
}
