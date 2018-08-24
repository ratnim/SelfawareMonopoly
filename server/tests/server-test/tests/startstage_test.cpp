#include <gmock/gmock.h>

#include <QSignalSpy>

#include <game/game.h>

#include <game/turn/startstate.h>
#include <game/turn/initstate.h>

#include <utils/exception.h>
#include <utils/program.h>

namespace
{
const QString player("Heinz");
}

TEST(StartStateTest, start_game)
{
    Game game;
    InitState previousState(&game);

    QSignalSpy start_spy(&game, &Game::onGameStart);
    QSignalSpy turn_spy(&game, &Game::onTurnChange);

	game.stateChange<StartState>(&previousState, std::vector<Player>({ { player } }));

    EXPECT_EQ(start_spy.size(), 1);
    EXPECT_EQ(turn_spy.size(), 1);
}

TEST(StartStateTest, roll_dice)
{
    Game game;
    InitState previousState(&game);
    game.stateChange<StartState>(&previousState, std::vector<Player>({ { player } }));

    QSignalSpy roll_spy(&game, &Game::onRollDice);
    QSignalSpy move_spy(&game, &Game::onPlayerMove);

    game.rollDice(player);

    EXPECT_EQ(roll_spy.size(), 1);
    EXPECT_EQ(move_spy.size(), 1);
}