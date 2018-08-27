#include <gmock/gmock.h>

#include <game/bank/bankaccount.h>

TEST(BankAccountTest, transfer_to)
{
    auto bank = BankAccount(std::numeric_limits<int>::max());
    BankAccount playerAccount;

	bank.transferTo(playerAccount, 1000);

	EXPECT_EQ(1000, playerAccount.balance());
}