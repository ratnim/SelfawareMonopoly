#include <gmock/gmock.h>

#include <QSignalSpy>

#include <game/game.h>

#include <game/turn/initstate.h>
#include <game/turn/rollstate.h>

#include <utils/exception.h>

namespace
{
const QString player_1("Heinz");
const QString player_2("Gertrude");
}

TEST(InitStateTest, player_join)
{
    Game game;

    QSignalSpy join_spy(&game, &Game::onPlayerJoin);

    game.playerJoin(player_1);

	EXPECT_EQ(join_spy.size(), 1);
    EXPECT_EQ(join_spy.at(0).at(0).toString(), player_1);

    EXPECT_THROW(game.playerJoin(player_1), Exception);

    game.playerJoin(player_2);
    EXPECT_EQ(join_spy.at(1).at(0).toString(), player_2);
    EXPECT_EQ(join_spy.size(), 2);
}

TEST(InitStateTest, player_ready)
{
    Game game;

    QSignalSpy ready_spy(&game, &Game::onPlayerReady);

    game.playerJoin(player_1);
    game.playerJoin(player_2);

    game.playerReady(player_1);

    EXPECT_EQ(ready_spy.size(), 1);
    EXPECT_THROW(game.playerReady(player_1), Exception);

    game.playerReady(player_2);
    EXPECT_EQ(ready_spy.size(), 2);
}

TEST(InitStateTest, start_game)
{
    Game game;

	EXPECT_THROW(game.gameStart(), Exception);

    game.playerJoin(player_1);
    game.playerJoin(player_2);

	EXPECT_THROW(game.gameStart(), Exception);

    game.playerReady(player_1);

	EXPECT_THROW(game.gameStart(), Exception);

    game.playerReady(player_2);

	game.gameStart();
	EXPECT_NE(nullptr, dynamic_cast<RollState*>(game.state()));
}

TEST(InitStateTest, possible_requests)
{
    Game game;

	QSignalSpy request_spy(&game, &Game::onPossibleRequests);

    game.playerJoin(player_1);
    game.playerJoin(player_2);

	game.possibleRequests(player_1);

    EXPECT_EQ(request_spy.at(0).at(0).toString(), player_1);

	game.possibleRequests(player_2);

	EXPECT_EQ(request_spy.at(1).at(0).toString(), player_2);
}

TEST(InitStateTest, update_possible_actions)
{
    Game game;

	QSignalSpy request_spy(&game, &Game::onPossibleRequests);

    game.playerJoin(player_1);
    EXPECT_EQ(1, request_spy.size());

    game.playerJoin(player_2);
    EXPECT_EQ(3, request_spy.size());

    game.playerReady(player_1);
    EXPECT_EQ(5, request_spy.size());

    game.playerReady(player_2);
    EXPECT_EQ(7, request_spy.size());
}
