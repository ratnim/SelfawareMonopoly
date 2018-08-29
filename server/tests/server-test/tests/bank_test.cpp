#include <gmock/gmock.h>

#include <QString>

#include <game/bank/bank.h>

#include <utils/exception.h>

TEST(BankTest, create_account)
{
    Bank bank;
    QString player_1("player1");
    QString player_2("player2");

	EXPECT_THROW(bank.balance(player_1), Exception);

    bank.createAccount(player_1);
    EXPECT_EQ(0, bank.balance(player_1));
    EXPECT_THROW(bank.createAccount(player_1), Exception);

    bank.createAccount(player_2, 1000);
    EXPECT_EQ(1000, bank.balance(player_2));
}

TEST(BankTest, transaction_with_the_bank)
{
    Bank bank;
    QString player("player");
    EXPECT_THROW(bank.giveMoney(player, 1000), Exception);
    EXPECT_THROW(bank.takeMoney(player, 500), Exception);
    bank.createAccount(player);

    EXPECT_EQ(0, bank.balance(player));
    bank.giveMoney(player, 1000);
    EXPECT_EQ(1000, bank.balance(player));
	bank.takeMoney(player, 500);
    EXPECT_EQ(1000, bank.balance(player));

    EXPECT_THROW(bank.takeMoney(player, 1000), Exception);
}

TEST(BankTest, transfer_not_enough_money)
{
    //BankAccount sender;
    //BankAccount reciever;

 //   EXPECT_FALSE(sender.transferTo(reciever, 1000));

	//EXPECT_EQ(0, sender.balance());
 //   EXPECT_EQ(0, reciever.balance());
}