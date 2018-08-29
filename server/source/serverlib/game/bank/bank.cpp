#include "bank.h"

#include <utils/exception.h>

void Bank::createAccount(const QString& name, int deposit)
{
	if (m_accounts.find(name) != m_accounts.end())
	{
        throw Exception("Bank account already exists.", Error::InternalError);
	}

	m_accounts.emplace(name, deposit);
}

void Bank::transferMoney(const QString& reciever, int amount)
{

}

void Bank::takeMoney(const QString& debtor, int debt)
{
    auto& it = m_accounts.find(debtor);
    if (it == m_accounts.end())
    {
        throw Exception("Bank account does not exists.", Error::InternalError);
    }

	if (it->second < debt)
	{
        throw Exception("Not sufficent money on bank account to pay debt.", Error::UnsupportedAction);
	}

	it->second -= debt;

    emit onMoneyChange(it->first, it->second);

}

void Bank::giveMoney(const QString& reciever, int amount)
{
    auto& it = m_accounts.find(reciever);
    if (it == m_accounts.end())
    {
        throw Exception("Bank account does not exists.", Error::InternalError);
    }

	it->second += amount;

	emit onMoneyChange(it->first, it->second);
}

int Bank::balance(const QString& name) const
{
    auto& it = m_accounts.find(name);
    if (it == m_accounts.end())
    {
        throw Exception("Bank account does not exists.", Error::InternalError);
    }

	return it->second;
}
