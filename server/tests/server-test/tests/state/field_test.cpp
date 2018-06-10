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
    player.canRoll = false;

	std::unique_ptr<Buddhist> buddhist = std::make_unique<Field>(player);

	buddhist.reset(buddhist->die());

	EXPECT_TRUE(dynamic_cast<Free*>(buddhist.get()));
}

TEST(FieldTest, field_to_roll)
{
    std::unique_ptr<Buddhist> buddhist = std::make_unique<Field>(Player{});

    buddhist.reset(buddhist->die());

    EXPECT_TRUE(dynamic_cast<Roll*>(buddhist.get()));
}

TEST(FieldTest, field_to_bankrupt)
{
    Player player;
    player.position = BOARD_SIZE + 1;

    std::unique_ptr<Buddhist> buddhist = std::make_unique<Field>(player);

    buddhist.reset(buddhist->die());

    EXPECT_TRUE(dynamic_cast<Bankrupt*>(buddhist.get()));
}
