#include "bankaccount.h"

BankAccount::BankAccount(int deposit)
    : m_deposit(deposit)
{
}

bool BankAccount::transferTo(BankAccount& other, int amount)
{
    if (amount >= 0 && m_deposit < amount)
        return false;

    this->m_deposit -= amount;
    other.m_deposit += amount;

	return true;
}

int BankAccount::balance() const
{
    return m_deposit;
}
