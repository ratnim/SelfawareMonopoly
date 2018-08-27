#include "bankaccount.h"

BankAccount::BankAccount(int deposit)
    : m_deposit(deposit)
{
}

void BankAccount::transferTo(BankAccount& other, int amount)
{
    this->m_deposit -= amount;
    other.m_deposit += amount;
}

int BankAccount::balance() const
{
    return m_deposit;
}
