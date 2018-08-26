#include <gmock/gmock.h>

#include <QSignalSpy>

#include <game/game.h>
#include <game/turn/initstate.h>
#include <utils/exception.h>

TEST(GameTest, init_state)
{
    Game game;
    EXPECT_NE(nullptr, dynamic_cast<InitState*>(game.state()));
}

TEST(GameTest, start_game)
{
    Game game;

    QSignalSpy start_spy(&game, &Game::onGameStart);

    EXPECT_THROW(game.gameStart(), Exception);

    game.playerJoin("Heinz");
    game.playerJoin("Gertrude");
    game.playerJoin("Else");

    EXPECT_THROW(game.gameStart(), Exception);

    game.playerReady("Heinz");
    game.playerReady("Gertrude");

    EXPECT_THROW(game.gameStart(), Exception);

    game.playerReady("Else");

    EXPECT_EQ(start_spy.size(), 0);
    game.gameStart();
    EXPECT_EQ(start_spy.size(), 1);
}

TEST(GameTest, simple_start_turn)
{
    Game game;

    QSignalSpy start_spy(&game, &Game::onTurnChange);

    game.playerJoin("Heinz");
    game.playerJoin("Gertrude");

    game.playerReady("Heinz");
    game.playerReady("Gertrude");

    EXPECT_EQ(start_spy.size(), 0);
    game.gameStart();
    ASSERT_EQ(start_spy.size(), 1);

    EXPECT_THROW(game.playerReady("Heinz"), Exception);
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
