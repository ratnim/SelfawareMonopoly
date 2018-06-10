#include <gmock/gmock.h>

#include <memory>

#include <game/jail.h>
#include <game/player.h>

#include <game/state/active/buddhist.h>
#include <game/state/active/pay.h>
#include <game/state/active/reborn.h>
#include <game/state/active/roll.h>

TEST(RebornTest, reborn_initalize)
{
    std::unique_ptr<Buddhist> buddhist = std::make_unique<Reborn>(Player{});

    EXPECT_TRUE(dynamic_cast<Reborn*>(buddhist.get()));
}

TEST(RebornTest, reborn_transition_to_roll)
{
    std::unique_ptr<Buddhist> buddhist = std::make_unique<Reborn>(Player{});

    buddhist.reset(buddhist->die());

    EXPECT_TRUE(dynamic_cast<Roll*>(buddhist.get()));
}

TEST(RebornTest, reborn_transition_to_pay)
{
    Player player;
    {  // 1. Turn
        std::unique_ptr<Buddhist> buddhist = std::make_unique<Reborn>(player);
        buddhist.reset(buddhist->die());

        EXPECT_TRUE(dynamic_cast<Roll*>(buddhist.get()));

        player.jail().jail();
    }
    {  // 2. Turn
        std::unique_ptr<Buddhist> buddhist = std::make_unique<Reborn>(player);
        buddhist.reset(buddhist->die());

        EXPECT_TRUE(dynamic_cast<Roll*>(buddhist.get()));
    }
    {  // 3. Turn
        std::unique_ptr<Buddhist> buddhist = std::make_unique<Reborn>(player);
        buddhist.reset(buddhist->die());

        EXPECT_TRUE(dynamic_cast<Pay*>(buddhist.get()));
    }
}
