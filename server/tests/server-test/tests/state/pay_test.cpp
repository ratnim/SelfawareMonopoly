#include <gmock/gmock.h>

#include <memory>

#include <game/jail.h>
#include <game/player.h>

#include <game/state/active/bankrupt.h>
#include <game/state/active/buddhist.h>
#include <game/state/active/roll.h>
#include <game/state/active/pay.h>

TEST(PayTest, pay_to_bankrupt)
{
    Player player;
    Jail jail;
	std::unique_ptr<Buddhist> buddhist = std::make_unique<Pay>(player, jail);

	buddhist.reset(buddhist->die());

	EXPECT_TRUE(dynamic_cast<Bankrupt*>(buddhist.get()));
}

TEST(PayTest, pay_to_roll)
{
    Player player;
    Jail jail;
    std::unique_ptr<Buddhist> buddhist = std::make_unique<Pay>(player, jail);

	buddhist->handle(ActiveAction::PAY);
    buddhist.reset(buddhist->die());

    EXPECT_TRUE(dynamic_cast<Roll*>(buddhist.get()));
}
