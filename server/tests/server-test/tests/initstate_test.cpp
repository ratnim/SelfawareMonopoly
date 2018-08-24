#include <gmock/gmock.h>

#include <QSignalSpy>

#include <game/game.h>

#include <game/turn/initstate.h>
#include <game/turn/startstate.h>

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

	EXPECT_THROW(game.gameStart(), Exception);
}
