#include <gmock/gmock.h>

#include <QSignalSpy>

#include <game/game.h>

#include <game/turn/startstate.h>
#include <game/turn/rollstate.h>

#include <utils/exception.h>

namespace
{
const QString player_1("Heinz");
const QString player_2("Gertrude");
}

TEST(RollStateTest, roll_dice)
{
    Game game;
    game.stateChange<StartState>(std::vector<Player>({ { player_1, player_2 } }));

    QSignalSpy roll_spy(&game, &Game::onRollDice);
    QSignalSpy move_spy(&game, &Game::onPlayerMove);

    game.rollDice(player_1);

    EXPECT_EQ(roll_spy.size(), 1);
    EXPECT_EQ(move_spy.size(), 1);
}