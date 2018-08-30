#include <gmock/gmock.h>

#include <QSignalSpy>

#include <models/boardmodel.h>

#include <game/game.h>
#include <game/turn/initstate.h>
#include <game/turn/idlestate.h>
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

    EXPECT_THROW(game.requestGameStart(), Exception);

    game.requestPlayerJoin("Heinz");
    game.requestPlayerJoin("Gertrude");
    game.requestPlayerJoin("Else");

    EXPECT_THROW(game.requestGameStart(), Exception);

    game.requestPlayerReady("Heinz");
    game.requestPlayerReady("Gertrude");

    EXPECT_THROW(game.requestGameStart(), Exception);

    game.requestPlayerReady("Else");

    EXPECT_EQ(start_spy.size(), 0);
    game.requestGameStart();
    EXPECT_EQ(start_spy.size(), 1);
}

TEST(GameTest, money_change_signal)
{
    Game game;
    QSignalSpy money_spy(&game, &Game::onMoneyChange);
    game.requestPlayerJoin("Heinz");
    game.requestPlayerJoin("Gertrude");
    game.requestPlayerReady("Heinz");
    game.requestPlayerReady("Gertrude");
    game.requestGameStart();

    EXPECT_EQ(2, money_spy.size());
}

TEST(GameTest, simple_start_turn)
{
    auto& instance = BoardModel::instance();
    auto board = std::move(instance.newBoard("berlin.json"));
    Game game(std::move(board));

    QSignalSpy start_spy(&game, &Game::onTurnChange);

    game.requestPlayerJoin("Heinz");
    game.requestPlayerJoin("Gertrude");

    game.requestPlayerReady("Heinz");
    game.requestPlayerReady("Gertrude");

    EXPECT_EQ(start_spy.size(), 0);
    game.requestGameStart();
    ASSERT_EQ(start_spy.size(), 1);

    EXPECT_THROW(game.requestPlayerReady("Heinz"), Exception);
    EXPECT_THROW(game.requestEndTurn("Heinz"), Exception);

    auto player = start_spy.at(0).at(0).toString();
    game.requestRollDice(player);
    if (player == "Gertrude")
    {
        EXPECT_THROW(game.requestRollDice("Heinz"), Exception);
        EXPECT_THROW(game.requestEndTurn("Heinz"), Exception);
    }
    else
    {
        EXPECT_THROW(game.requestRollDice("Gertrude"), Exception);
        EXPECT_THROW(game.requestEndTurn("Gertrude"), Exception);
    }
}

TEST(GameTest, go_to_jail_position)
{

	auto& instance = BoardModel::instance();
	auto board = std::move(instance.newBoard("berlin.json"));

    Game game(std::move(board));
    game.requestPlayerJoin("Heinz");
    game.requestPlayerJoin("Gertrude");
    game.requestPlayerReady("Heinz");
    game.requestPlayerReady("Gertrude");
    game.requestGameStart();

	game.doMoveCurrentPlayer(30);

	EXPECT_TRUE(game.currentPlayer().inJail());
	EXPECT_NE(nullptr, dynamic_cast<IdleState*>(game.state()));
}
