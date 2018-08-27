#include <gmock/gmock.h>

#include <game/bank/bankaccount.h>

TEST(BankAccountTest, transfer_to)
{
    BankAccount sender(1000);
    BankAccount reciever;

	EXPECT_TRUE(sender.transferTo(reciever, 1000));

	EXPECT_EQ(0, sender.balance());
	EXPECT_EQ(1000, reciever.balance());
}

TEST(BankAccountTest, transfer_not_enough_money)
{
    BankAccount sender;
    BankAccount reciever;

    EXPECT_FALSE(sender.transferTo(reciever, 1000));

	EXPECT_EQ(0, sender.balance());
    EXPECT_EQ(0, reciever.balance());
}