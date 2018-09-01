#include <gmock/gmock.h>

#include <QSignalSpy>

#include <game/game.h>

#include <game/turn/initstate.h>
#include <game/turn/movestate.h>

#include <utils/exception.h>

#include <test_utils/helpers.h>


namespace
{
const QString player_1("Heinz");
const QString player_2("Gertrude");
}

TEST(InitStateTest, player_join)
{
    Game game;

    QSignalSpy join_spy(&game, &Game::onPlayerJoin);

    game.requestPlayerJoin(player_1);

	EXPECT_EQ(join_spy.size(), 1);
    EXPECT_EQ(join_spy.at(0).at(0).toString(), player_1);

    EXPECT_THROW(game.requestPlayerJoin(player_1), Exception);

    game.requestPlayerJoin(player_2);
    EXPECT_EQ(join_spy.at(1).at(0).toString(), player_2);
    EXPECT_EQ(join_spy.size(), 2);
}

TEST(InitStateTest, player_ready)
{
    Game game;

    QSignalSpy ready_spy(&game, &Game::onPlayerReady);

    game.requestPlayerJoin(player_1);
    game.requestPlayerJoin(player_2);

    game.requestPlayerReady(player_1);

    EXPECT_EQ(ready_spy.size(), 1);
    EXPECT_THROW(game.requestPlayerReady(player_1), Exception);

    game.requestPlayerReady(player_2);
    EXPECT_EQ(ready_spy.size(), 2);
}

TEST(InitStateTest, start_game)
{
    Game game;

	EXPECT_THROW(game.requestGameStart(), Exception);

    game.requestPlayerJoin(player_1);
    game.requestPlayerJoin(player_2);

	EXPECT_THROW(game.requestGameStart(), Exception);

    game.requestPlayerReady(player_1);

	EXPECT_THROW(game.requestGameStart(), Exception);

    game.requestPlayerReady(player_2);

	game.requestGameStart();
	EXPECT_NE(nullptr, dynamic_cast<MoveState*>(game.state()));
}

TEST(InitStateTest, possible_requests)
{
    Game game;

	QSignalSpy request_spy(&game, &Game::onPossibleRequests);

    game.requestPlayerJoin(player_1);
    game.requestPlayerJoin(player_2);
	game.requestPossibleRequests(player_1);

    EXPECT_EQ(request_spy.last().at(0).toString(), player_1);
    EXPECT_TRUE(containsRequest(request_spy.last().at(1).toJsonArray(), "player_ready"));
    EXPECT_FALSE(containsRequest(request_spy.last().at(1).toJsonArray(), "game_start"));

	game.requestPossibleRequests(player_2);

	EXPECT_EQ(request_spy.last().at(0).toString(), player_2);
    EXPECT_TRUE(containsRequest(request_spy.last().at(1).toJsonArray(), "player_ready"));
    EXPECT_FALSE(containsRequest(request_spy.last().at(1).toJsonArray(), "game_start"));

	game.requestPlayerReady(player_1);
    game.requestPlayerReady(player_2);

    EXPECT_FALSE(containsRequest(request_spy.last().at(1).toJsonArray(), "player_ready"));
    EXPECT_TRUE(containsRequest(request_spy.last().at(1).toJsonArray(), "game_start"));
}

TEST(InitStateTest, update_possible_actions)
{
    Game game;

	QSignalSpy request_spy(&game, &Game::onPossibleRequests);

    game.requestPlayerJoin(player_1);
    EXPECT_EQ(1, request_spy.size());

    game.requestPlayerJoin(player_2);
    EXPECT_EQ(3, request_spy.size());

    game.requestPlayerReady(player_1);
    EXPECT_EQ(5, request_spy.size());

    game.requestPlayerReady(player_2);
    EXPECT_EQ(7, request_spy.size());
}
