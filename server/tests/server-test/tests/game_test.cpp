#include <gmock/gmock.h>

#include <QSignalSpy>

#include <game/game.h>
#include <utils/exception.h>

TEST(GameTest, join_multiple_times)
{
    Game game;

    QSignalSpy join_spy(&game, &Game::onPlayerJoin);

    game.join("Heinz");

    EXPECT_THROW(game.join("Heinz"), Exception);

    game.join("Gertrude");

    EXPECT_EQ(join_spy.size(), 2);
    EXPECT_EQ(join_spy.at(0).at(0).toString(), "Heinz");
    EXPECT_EQ(join_spy.at(1).at(0).toString(), "Gertrude");
}

TEST(GameTest, ready)
{
    Game game;

    QSignalSpy ready_spy(&game, &Game::onPlayerReady);

    game.join("Heinz");
    game.join("Gertrude");

    EXPECT_THROW(game.ready("Else"), Exception);
    EXPECT_EQ(ready_spy.size(), 0);

    game.ready("Heinz");

    EXPECT_EQ(ready_spy.size(), 1);
    EXPECT_THROW(game.ready("Heinz"), Exception);

    game.ready("Gertrude");
    EXPECT_EQ(ready_spy.size(), 2);

    game.start();
}

TEST(GameTest, start_game)
{
    Game game;

    QSignalSpy start_spy(&game, &Game::onGameStart);

    EXPECT_THROW(game.start(), Exception);

    game.join("Heinz");
    game.join("Gertrude");
    game.join("Else");

    EXPECT_THROW(game.start(), Exception);

    game.ready("Heinz");
    game.ready("Gertrude");

    EXPECT_THROW(game.start(), Exception);

    game.ready("Else");

    EXPECT_EQ(start_spy.size(), 0);
    game.start();
    EXPECT_EQ(start_spy.size(), 1);
}

TEST(GameTest, simple_start_turn)
{
    Game game;

    QSignalSpy start_spy(&game, &Game::onTurnChange);

    game.join("Heinz");
    game.join("Gertrude");

    game.ready("Heinz");
    game.ready("Gertrude");

    EXPECT_EQ(start_spy.size(), 0);
    game.start();
    ASSERT_EQ(start_spy.size(), 1);

    EXPECT_THROW(game.ready("Heinz"), Exception);
    EXPECT_THROW(game.endTurn("Heinz"), Exception);

    auto player = start_spy.at(0).at(0).toString();
    game.rollDice(player);
    if (player == "Gertrude")
    {
        EXPECT_THROW(game.rollDice("Heinz"), Exception);
        EXPECT_THROW(game.endTurn("Heinz"), Exception);
    }
    else
    {
        EXPECT_THROW(game.rollDice("Gertrude"), Exception);
        EXPECT_THROW(game.endTurn("Gertrude"), Exception);
    }
}
