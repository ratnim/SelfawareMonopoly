#include <gmock/gmock.h>

#include <QSignalSpy>

#include <game/game.h>

#include <game/turn/jailstate.h>
#include <game/turn/idlestate.h>

#include <utils/exception.h>

#include <test_utils/helpers.h>

namespace
{
const QString player_1("Heinz");
const QString player_2("Gertrude");
}

TEST(JailStateTest, state_transfer_to_idle)
{
    Game game;
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.currentPlayer().jail();
    game.stateChange<JailState>();

	EXPECT_EQ(player_1, game.currentPlayer().name());
    game.rollDice(player_1);
    EXPECT_NE(nullptr, dynamic_cast<IdleState*>(game.state()));
}

TEST(JailStateTest, roll_dice_false_player)
{
    Game game;
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.currentPlayer().jail();
    game.stateChange<JailState>();

    EXPECT_EQ(player_1, game.currentPlayer().name());
    EXPECT_THROW(game.rollDice(player_2), Exception);
}

TEST(JailStateTest, roll_dice_no_pash)
{
    Game game;
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.currentPlayer().jail();
    game.stateChange<JailState>();

    EXPECT_EQ(player_1, game.currentPlayer().name());
    game.rollDice(player_1); // need to be no pash

	EXPECT_TRUE(game.currentPlayer().inJail());
}

TEST(JailStateTest, roll_dice_pash)
{
    Game game;
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.currentPlayer().jail();
    game.stateChange<JailState>();

    EXPECT_EQ(player_1, game.currentPlayer().name());
    game.rollDice(player_1);  // need to be a pash

	EXPECT_FALSE(game.currentPlayer().inJail());
}

TEST(JailStateTest, possible_requests)
{
    Game game;
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    QSignalSpy request_spy(&game, &Game::onPossibleRequests);
    game.currentPlayer().jail();
    game.stateChange<JailState>();

    game.possibleRequests(player_1);

    EXPECT_EQ(player_1, game.currentPlayer().name());
    EXPECT_EQ(player_1, request_spy.last().at(0).toString());
    EXPECT_TRUE(containsRequest(request_spy.last().at(1).toJsonArray(), "roll_dice"));

    game.possibleRequests(player_2);

    EXPECT_EQ(request_spy.last().at(0).toString(), player_2);
    EXPECT_FALSE(containsRequest(request_spy.last().at(1).toJsonArray(), "roll_dice"));
}

TEST(JailStateTest, update_possible_actions)
{
    Game game;
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    QSignalSpy request_spy(&game, &Game::onPossibleRequests);

    game.stateChange<JailState>();
    EXPECT_EQ(2, request_spy.size());
}