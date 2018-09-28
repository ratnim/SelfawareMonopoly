#include "bank.h"

#include <utils/exception.h>

void Bank::createAccount(const QString& name, int deposit)
{
    if (m_accounts.find(name) != m_accounts.end())
    {
        throw Exception("Bank account already exists.", Error::InternalError);
    }

    m_accounts.emplace(name, 0);
    changeDeposit(name, deposit);
}

void Bank::transferMoney(const QString& sender, const QString& reciever, int amount)
{
    const auto& senderIt = m_accounts.find(sender);
    if (senderIt == m_accounts.end())
    {
        throw Exception("Bank account does not exists.", Error::InternalError);
    }

    if (senderIt->second < amount)
    {
        throw Exception("Not sufficent money on bank account to pay debt.", Error::UnsupportedAction);
    }

    if (reciever.isEmpty())
    {
        takeMoney(sender, amount);
    }
    else
    {
        const auto& recieverIt = m_accounts.find(reciever);
        if (recieverIt == m_accounts.end())
        {
            throw Exception("Bank account does not exists.", Error::InternalError);
        }

        changeDeposit(sender, -amount);
        changeDeposit(reciever, amount);
    }
}

void Bank::takeMoney(const QString& debtor, int debt)
{
    const auto& it = m_accounts.find(debtor);
    if (it == m_accounts.end())
    {
        throw Exception("Bank account does not exists.", Error::InternalError);
    }

    if (it->second < debt)
    {
        throw Exception("Not sufficent money on bank account to pay debt.", Error::UnsupportedAction);
    }

    changeDeposit(debtor, -debt);
}

void Bank::giveMoney(const QString& reciever, int amount)
{
    if (m_accounts.find(reciever) == m_accounts.end())
    {
        throw Exception("Bank account does not exists.", Error::InternalError);
    }

    changeDeposit(reciever, amount);
}

int Bank::balance(const QString& name) const
{
    const auto& it = m_accounts.find(name);
    if (it == m_accounts.end())
    {
        throw Exception("Bank account does not exists.", Error::InternalError);
    }

    return it->second;
}

void Bank::changeDeposit(const QString& name, int amount)
{
    m_accounts[name] += amount;
    emit onMoneyChange(name, m_accounts[name]);
}