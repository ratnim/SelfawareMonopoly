#pragma once

class BankAccount
{
public: 
	BankAccount(int deposit = 0);

	bool transferTo(BankAccount& other, int amount);
    int balance() const;

protected:
    int m_deposit;
};
