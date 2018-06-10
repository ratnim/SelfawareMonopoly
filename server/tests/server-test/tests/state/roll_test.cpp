#include <gmock/gmock.h>

#include <memory>

#include <game/jail.h>
#include <game/player.h>

#include <game/state/active/buddhist.h>
#include <game/state/active/field.h>
#include <game/state/active/free.h>
#include <game/state/active/roll.h>

TEST(RollTest, roll_to_roll)
{
    Player player;
    Jail jail;
    std::unique_ptr<Buddhist> buddhist = std::make_unique<Roll>(player, jail);

    buddhist.reset(buddhist->die());

    EXPECT_TRUE(dynamic_cast<Roll*>(buddhist.get()));
}

TEST(RollTest, roll_to_field)
{
    Player player;
    Jail jail;
    std::unique_ptr<Buddhist> buddhist = std::make_unique<Roll>(player, jail);

    buddhist->handle(ActiveAction::ROLL_DICE);
    buddhist.reset(buddhist->die());

    EXPECT_TRUE(dynamic_cast<Field*>(buddhist.get()));
}

TEST(RollTest, roll_to_free)
{
    Player player;
    Jail jail;

    {
        std::unique_ptr<Buddhist> buddhist = std::make_unique<Roll>(player, jail);
        auto roll = dynamic_cast<Roll*>(buddhist.get());
        roll->watsonRoll(Dices{ 6, 6 });
        buddhist.reset(buddhist->die());

		EXPECT_TRUE(dynamic_cast<Field*>(buddhist.get()));
    }
    {
        std::unique_ptr<Buddhist> buddhist = std::make_unique<Roll>(player, jail);
        auto roll = dynamic_cast<Roll*>(buddhist.get());
        roll->watsonRoll(Dices{ 6, 6 });
        buddhist.reset(buddhist->die());
        
		EXPECT_TRUE(dynamic_cast<Field*>(buddhist.get()));
    }
    {
        std::unique_ptr<Buddhist> buddhist = std::make_unique<Roll>(player, jail);
        auto roll = dynamic_cast<Roll*>(buddhist.get());
        roll->watsonRoll(Dices{ 6, 6 });
        buddhist.reset(buddhist->die());

		EXPECT_TRUE(jail.inJail());
        EXPECT_TRUE(dynamic_cast<Free*>(buddhist.get()));
    }
}
