#include <gmock/gmock.h>

#include <QString>

#include <game/bank/bank.h>

#include <utils/exception.h>

TEST(BankTest, create_account)
{
    Bank bank;
    QString player_1("player");
    QString player_2("player");

	EXPECT_THROW(bank.balance(player_1), Exception);
    bank.createAccount(player_1);
    EXPECT_EQ(0, bank.balance(player_1));

    bank.createAccount(player_2, 1000);
    EXPECT_EQ(0, bank.balance(player_2));
}

TEST(BankTest, create_money)
{
    Bank bank;
    QString player("player");
    EXPECT_THROW(bank.transferMoney(player, 1000), Exception);
    bank.createAccount(player);

    EXPECT_EQ(0, bank.balance(player));
    bank.transferMoney(player, 1000);
    EXPECT_EQ(1000, bank.balance(player));
}

TEST(BankTest, transfer_not_enough_money)
{
    //BankAccount sender;
    //BankAccount reciever;

 //   EXPECT_FALSE(sender.transferTo(reciever, 1000));

	//EXPECT_EQ(0, sender.balance());
 //   EXPECT_EQ(0, reciever.balance());
}