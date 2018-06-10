#include <gmock/gmock.h>

#include <memory>

#include <game/jail.h>
#include <game/player.h>

#include <game/state/active/bankrupt.h>
#include <game/state/active/field.h>
#include <game/state/active/free.h>
#include <game/state/active/roll.h>

TEST(FieldTest, field_to_free)
{
    Player player;
    Jail jail;
    player.canRoll = false;
	std::unique_ptr<Buddhist> buddhist = std::make_unique<Field>(player, jail);

	buddhist.reset(buddhist->die());

	EXPECT_TRUE(dynamic_cast<Free*>(buddhist.get()));
}

TEST(FieldTest, field_to_roll)
{
    Player player;
    Jail jail;
    std::unique_ptr<Buddhist> buddhist = std::make_unique<Field>(player, jail);

    buddhist.reset(buddhist->die());

    EXPECT_TRUE(dynamic_cast<Roll*>(buddhist.get()));
}

TEST(FieldTest, field_to_bankrupt)
{
    Player player;
    Jail jail;
    player.position = BOARD_SIZE + 1;
    std::unique_ptr<Buddhist> buddhist = std::make_unique<Field>(player, jail);

    buddhist.reset(buddhist->die());

    EXPECT_TRUE(dynamic_cast<Bankrupt*>(buddhist.get()));
}
