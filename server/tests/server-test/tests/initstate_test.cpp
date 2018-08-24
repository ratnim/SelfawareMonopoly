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

TEST(InitStateTest, start_game)
{
    Game game;
   
    QSignalSpy start_spy(&game, &Game::onGameStart);
    QSignalSpy turn_spy(&game, &Game::onTurnChange);

    EXPECT_EQ(start_spy.size(), 1);
    EXPECT_EQ(turn_spy.size(), 1);
}

TEST(InitStateTest, roll_dice)
{
    Game game;
    InitState previousState(&game);
    game.stateChange<StartState>(&previousState, std::vector<Player>({ { player_1 } }));

    QSignalSpy roll_spy(&game, &Game::onRollDice);
    QSignalSpy move_spy(&game, &Game::onPlayerMove);

    game.rollDice(player_1);

    EXPECT_EQ(roll_spy.size(), 1);
    EXPECT_EQ(move_spy.size(), 1);
}