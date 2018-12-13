#include <gmock/gmock.h>

#include <QSignalSpy>

#include <models/boardmodel.h>

#include <game/game.h>

#include <game/turn/jailstate.h>
#include <game/turn/idlestate.h>

#include <utils/exception.h>

#include <test_utils/helpers.h>

/*** Prime Path Coverage

void JailState::requestRollDice(const QString& playerName)
{
    // State 1
    ensurePlayersTurn(playerName); // State 2 on exception

    auto& player = m_game->currentPlayer();
    Dices dices = m_game->doCurrentPlayerRollDices();

    if (dices.isDouble())
    {
        // State 3
        player.leaveJail();
        m_game->doCurrentPlayerMove(dices.sum());
    } else {
        // State 4
        changeToDefaultState();
    }
    // State 5

 * Control Flow Graph
 *
 * directed from top to botteom:
 *
 *       1
 *       |
 *   +---+---+
 *   |   |   |
 *   3   4   2
     |   |
 *   +-+-+
 *     |
 *     5
 *
 * Start State: 1
 * Final State: 5
 *
 *
 * 3 requirements are needed for Prime Paths:
 * 1. [1,3,5]
 * 2. [1,4,5]
 * 3. [1,2]
 *
 */

namespace
{
const QString player_1("Heinz");
const QString player_2("Gertrude");
const QString player_not_playing("NotPlaying");
}

// states: [1,3,5]
TEST(JailStateTestPrimePaths, prime_graph_req_1){
    int32_t dice_number = 3;
    int32_t dices_sum = 2*dice_number;

    Game game(std::move(fieldsSingleJail()));

    game.players() = RingBuffer<Player>(std::vector<Player>{player_1, player_2});
    game.doCurrentPlayerGoToJail();
    game.stateChange<JailState>();
    EXPECT_TRUE(game.currentPlayer().inJail());
    int32_t old_pos = game.currentPlayer().position();
    game.watson().doManipulateNextRoll(player_1, dice_number, dice_number);
    game.requestRollDice(player_1);
    EXPECT_FALSE(game.currentPlayer().inJail());
    EXPECT_EQ((old_pos+dices_sum) % game.board().size(), game.currentPlayer().position());
}

// states: [1,4,5]
TEST(JailStateTestPrimePaths, prime_graph_req_2){
    int32_t dice_1_number = 3;
    int32_t dice_2_number = 2;
    int32_t dices_sum = dice_1_number + dice_2_number;

    Game game(std::move(fieldsSingleJail()));

    game.players() = RingBuffer<Player>(std::vector<Player>{player_1, player_2});
    game.doCurrentPlayerGoToJail();
    game.stateChange<JailState>();
    EXPECT_TRUE(game.currentPlayer().inJail());
    int32_t old_pos = game.currentPlayer().position();
    game.watson().doManipulateNextRoll(player_1, dice_1_number, dice_2_number);
    game.requestRollDice(player_1);
    EXPECT_TRUE(game.currentPlayer().inJail());
    EXPECT_EQ(old_pos+dices_sum, game.currentPlayer().position());
}

// states: [1,2]
TEST(JailStateTestPrimePaths, prime_graph_req_3){
    Game game;

    game.players() = RingBuffer<Player>(std::vector<Player>{player_1, player_2});
    game.doCurrentPlayerGoToJail();
    game.stateChange<JailState>();
    JailState jail_state = static_cast<JailState>(game.state());
    EXPECT_THROW(jail_state.requestRollDice(player_not_playing), Exception);
}