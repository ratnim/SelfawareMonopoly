#include <gmock/gmock.h>

#include <game/dices.h>
#include <utils/exception.h>

TEST(DicesTest, from_wrong_distance)
{
    EXPECT_THROW(Dices{ 1 }, Exception);
    EXPECT_THROW(Dices{ 13 }, Exception);
}

TEST(DicesTest, from_distance)
{
    {
        Dices dices{ 12 };
        EXPECT_EQ(12, dices.sum());
    }
    {
        Dices dices{ 8 };
        EXPECT_EQ(8, dices.sum());
    }
	{
        Dices dices{ 6 };
        EXPECT_EQ(6, dices.sum());
    }
    {
        Dices dices{ 3 };
        EXPECT_EQ(3, dices.sum());
    }
}
