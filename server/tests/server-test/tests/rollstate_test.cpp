#include <gmock/gmock.h>

#include <QSignalSpy>

#include <game/game.h>

#include <game/turn/idlestate.h>
#include <game/turn/rollstate.h>

#include <utils/exception.h>

#include <test_utils/helpers.h>

namespace
{
const QString player_1("Heinz");
const QString player_2("Gertrude");
}

TEST(RollStateTest, roll_dice)
{
    Game game;
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
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

TEST(RollStateTest, possible_requests)
{
    Game game;
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.stateChange<RollState>();
    QSignalSpy request_spy(&game, &Game::onPossibleRequests);

    game.possibleRequests(player_1);

    EXPECT_EQ(player_1, game.currentPlayer().name());
    EXPECT_EQ(player_1, request_spy.last().at(0).toString());
    EXPECT_TRUE(containsRequest(request_spy.last().at(1).toJsonArray(), "roll_dice"));

    game.possibleRequests(player_2);

    EXPECT_EQ(request_spy.last().at(0).toString(), player_2);
    EXPECT_FALSE(containsRequest(request_spy.last().at(1).toJsonArray(), "roll_dice"));
}

TEST(RollStateTest, update_possible_actions)
{
    Game game;
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    QSignalSpy request_spy(&game, &Game::onPossibleRequests);

    game.stateChange<RollState>();

    EXPECT_EQ(2, request_spy.size());

	EXPECT_EQ(player_1, game.currentPlayer().name());
    game.rollDice(player_1);
}