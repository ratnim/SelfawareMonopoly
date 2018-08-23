#include <gmock/gmock.h>

#include <QSignalSpy>

#include <game/stages/runstage.h>
#include <utils/exception.h>
#include <utils/program.h>

namespace
{
const QString player("Heinz");
}

TEST(RunStageTest, start_game)
{
    Game game;

    QSignalSpy start_spy(&game, &Game::onGameStart);
    QSignalSpy turn_spy(&game, &Game::onTurnChange);

	game.stateChange<RunStage>(&game, std::vector<Player>({ { player } }));

    EXPECT_EQ(start_spy.size(), 1);
    EXPECT_EQ(turn_spy.size(), 1);
}

TEST(RunStageTest, roll_dice)
{
    Game game;
    game.stateChange<RunStage>(&game, std::vector<Player>({ { player } }));

    QSignalSpy roll_spy(&game, &Game::onRollDice);
    QSignalSpy move_spy(&game, &Game::onPlayerMove);

    game.rollDice(player);

    EXPECT_EQ(roll_spy.size(), 1);
    EXPECT_EQ(move_spy.size(), 1);
}