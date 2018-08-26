#include <gmock/gmock.h>

#include <QSignalSpy>

#include <game/game.h>

#include <game/turn/rollstate.h>
#include <game/turn/idlestate.h>

#include <utils/exception.h>

namespace
{
const QString player_1("Heinz");
const QString player_2("Gertrude");
}

TEST(RollStateTest, roll_dice)
{
    Game game;
    game.players() = RingBuffer<Player>(std::vector<Player>{{player_1, player_2}});
    game.stateChange<RollState>();

    QSignalSpy roll_spy(&game, &Game::onRollDice);
    QSignalSpy move_spy(&game, &Game::onPlayerMove);


	EXPECT_EQ(player_1, game.currentPlayer().name());
    game.rollDice(player_1);

    EXPECT_EQ(roll_spy.size(), 1);
    EXPECT_EQ(move_spy.size(), 1);
}

TEST(RollStateTest, roll_dice_false_player)
{
    Game game;
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.stateChange<RollState>();

	EXPECT_EQ(player_1, game.currentPlayer().name());
    EXPECT_THROW(game.rollDice(player_2), Exception);
}

TEST(RollStateTest, state_transfer_to_idle)
{
    Game game;
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.stateChange<RollState>();

    EXPECT_EQ(player_1, game.currentPlayer().name());
    game.rollDice(player_1);
    EXPECT_NE(nullptr, dynamic_cast<IdleState*>(game.state()));
}
