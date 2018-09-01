#include <gmock/gmock.h>

#include <QString>
#include <QSignalSpy>

#include <game/bank/bank.h>

#include <utils/exception.h>

TEST(BankTest, create_account)
{
    Bank bank;
    QSignalSpy bank_spy(&bank, &Bank::onMoneyChange);
    QString player_1("player1");
    QString player_2("player2");

	EXPECT_THROW(bank.balance(player_1), Exception);

    bank.createAccount(player_1);
    EXPECT_EQ(0, bank.balance(player_1));
    EXPECT_EQ(1, bank_spy.size());
    EXPECT_THROW(bank.createAccount(player_1), Exception);

    bank.createAccount(player_2, 1000);
    EXPECT_EQ(1000, bank.balance(player_2));
    EXPECT_EQ(2, bank_spy.size());
}

TEST(BankTest, transaction_with_the_bank)
{
    Bank bank;
    QString player("player");
    QSignalSpy bank_spy(&bank, &Bank::onMoneyChange);
    EXPECT_THROW(bank.giveMoney(player, 1000), Exception);
    EXPECT_THROW(bank.takeMoney(player, 500), Exception);
    bank.createAccount(player);
	
	EXPECT_EQ(1, bank_spy.size());
    EXPECT_EQ(0, bank.balance(player));

    bank.giveMoney(player, 1000);
    EXPECT_EQ(1000, bank.balance(player));
    EXPECT_EQ(2, bank_spy.size());

	bank.takeMoney(player, 250);
    EXPECT_EQ(750, bank.balance(player));
    EXPECT_EQ(3, bank_spy.size());

    EXPECT_THROW(bank.takeMoney(player, 1000), Exception);
}

TEST(BankTest, emit_correct_signals)
{
    Bank bank;
    QString player("player");
    QSignalSpy bank_spy(&bank, &Bank::onMoneyChange);
    bank.createAccount(player);
    EXPECT_EQ(1, bank_spy.size());
    EXPECT_EQ(player, bank_spy.last().at(0).toString());
    EXPECT_EQ(0, bank_spy.last().at(1).toInt());

	bank.giveMoney(player, 1000);
    EXPECT_EQ(2, bank_spy.size());
    EXPECT_EQ(player, bank_spy.last().at(0).toString());
    EXPECT_EQ(1000, bank_spy.last().at(1).toInt());

	bank.giveMoney(player, 500);
    EXPECT_EQ(3, bank_spy.size());
    EXPECT_EQ(player, bank_spy.last().at(0).toString());
    EXPECT_EQ(1500, bank_spy.last().at(1).toInt());

    bank.takeMoney(player, 250);
    EXPECT_EQ(4, bank_spy.size());
    EXPECT_EQ(player, bank_spy.last().at(0).toString());
    EXPECT_EQ(1250, bank_spy.last().at(1).toInt());
}

TEST(BankTest, transfer_to_player)
{
    Bank bank;
    QSignalSpy bank_spy(&bank, &Bank::onMoneyChange);
    QString player_1("player1");
    QString player_2("player2");
    bank.createAccount(player_1);
    bank.createAccount(player_2);

	EXPECT_THROW(bank.transferMoney(player_1, player_2, 1000), Exception);

	bank.giveMoney(player_1, 1500);
    bank.transferMoney(player_1, player_2, 1000);

	EXPECT_EQ(500, bank.balance(player_1));
	EXPECT_EQ(1000, bank.balance(player_2));
}