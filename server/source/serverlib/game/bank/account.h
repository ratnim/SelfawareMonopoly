#pragma once

class BankAccount
{
public: 
	BankAccount(int deposit = 0);

	void transferTo(BankAccount& other, int amount);
    int balance() const;

protected:
    int m_deosit;
};
