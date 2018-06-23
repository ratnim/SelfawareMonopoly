#include <gmock/gmock.h>

#include <game/game.h>
#include <utils/exception.h>

TEST(GameTest, join)
{
    Game game;

    game.join("Heinz");

    EXPECT_THROW(game.join("Heinz"), Exception);

    game.join("Gertrude");
}

TEST(GameTest, start)
{
    Game game;

    EXPECT_THROW(game.start(), Exception);

    game.join("Heinz");
    game.join("Gertrude");
    game.join("Else");

    EXPECT_THROW(game.start(), Exception);

    game.ready("Heinz");
    game.ready("Gertrude");

    EXPECT_THROW(game.start(), Exception);

    game.ready("Else");

    game.start();
}

TEST(GameTest, ready)
{
    Game game;

    game.join("Heinz");
    game.join("Gertrude");

    EXPECT_THROW(game.ready("Else"), Exception);

    game.ready("Heinz");
    EXPECT_THROW(game.ready("Heinz"), Exception);

    game.ready("Gertrude");

    game.start();
}

TEST(GameTest, simple_start_turn)
{
    Game game;

    game.join("Heinz");
    game.join("Gertrude");

    game.ready("Heinz");
    game.ready("Gertrude");

    game.start();
    try
    {
        game.ready("Heinz");
        game.ready("Heinz");
        game.ready("Heinz");
    }
    catch (Exception)
    {
    }
    try
    {
        game.endTurn("Heinz");
    }
	catch (Exception)
	{
	}
    game.rollDice("Gertrude");
    EXPECT_THROW(game.rollDice("Gertrude"), Exception);
    EXPECT_THROW(game.rollDice("Gertrude"), Exception);
    game.endTurn("Gertrude");
}
