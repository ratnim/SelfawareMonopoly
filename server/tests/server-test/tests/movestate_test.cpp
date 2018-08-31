#include <gmock/gmock.h>

#include <QSignalSpy>

#include <memory>
#include <vector>

#include <models/boardmodel.h>

#include <game/game.h>
#include <game/board/field.h>

#include <game/turn/idlestate.h>
#include <game/turn/movestate.h>

#include <utils/exception.h>

#include <test_utils/helpers.h>

namespace
{
const QString player_1("Heinz");
const QString player_2("Gertrude");
}

TEST(MoveStateTest, roll_dice)
{
    Game game(std::move(fieldsFree()));
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.stateChange<MoveState>();

    QSignalSpy roll_spy(&game, &Game::onRollDice);
    QSignalSpy move_spy(&game, &Game::onPlayerMove);

    EXPECT_EQ(player_1, game.currentPlayer().name());
    game.watson_next_rolls.emplace(2, 2);
    game.requestRollDice(player_1);

    EXPECT_EQ(roll_spy.size(), 1);
    EXPECT_EQ(move_spy.size(), 1);
    EXPECT_EQ("forward", move_spy.last().at(2).toString().toStdString());
    EXPECT_EQ(4, move_spy.last().at(1).toInt());

	game.watson_next_rolls.emplace(1, 2);
    game.requestRollDice(player_1);

	EXPECT_EQ("forward", move_spy.last().at(2).toString().toStdString());
    EXPECT_EQ(2, move_spy.last().at(1).toInt());
}

TEST(MoveStateTest, money_on_pass_start)
{
    Game game(std::move(fieldsStart()));
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.stateChange<MoveState>();
    game.bank().createAccount(player_1, 0);
    game.bank().createAccount(player_2, 0);

    QSignalSpy money_spy(&game, &Game::onMoneyChange);

    EXPECT_EQ(player_1, game.currentPlayer().name());
    game.watson_next_rolls.emplace(2, 2);
    game.requestRollDice(player_1);

    EXPECT_EQ(money_spy.size(), 0);

    game.watson_next_rolls.emplace(1, 2);
    game.requestRollDice(player_1);
    EXPECT_EQ(money_spy.size(), 1);

	game.requestEndTurn(player_1);

	EXPECT_EQ(player_2, game.currentPlayer().name());
    game.watson_next_rolls.emplace(3, 3);
    game.requestRollDice(player_2);

    EXPECT_EQ(money_spy.size(), 2);
	EXPECT_EQ(player_2, game.currentPlayer().name());
    game.watson_next_rolls.emplace(1, 2);
    game.requestRollDice(player_2);

     EXPECT_EQ(money_spy.size(), 2);
}

TEST(MoveStateTest, roll_dice_1_pash)
{
    Game game(std::move(fieldsFree()));

    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.stateChange<MoveState>();

    QSignalSpy roll_spy(&game, &Game::onRollDice);
    QSignalSpy move_spy(&game, &Game::onPlayerMove);

    EXPECT_EQ(player_1, game.currentPlayer().name());
    game.watson_next_rolls.emplace(6, 6);
    game.requestRollDice(player_1);

    EXPECT_EQ(roll_spy.size(), 1);
    EXPECT_EQ(move_spy.size(), 1);
    EXPECT_NE(nullptr, dynamic_cast<MoveState*>(game.state()));

    game.watson_next_rolls.emplace(1, 2);
    game.requestRollDice(player_1);

    EXPECT_EQ(roll_spy.size(), 2);
    EXPECT_EQ(move_spy.size(), 2);
    EXPECT_NE(nullptr, dynamic_cast<IdleState*>(game.state()));
}

TEST(MoveStateTest, roll_dice_pash_3_times)
{
    Game game(std::move(fieldsSingleJail()));

    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.stateChange<MoveState>();

    QSignalSpy roll_spy(&game, &Game::onRollDice);
    QSignalSpy move_spy(&game, &Game::onPlayerMove);

    EXPECT_EQ(player_1, game.currentPlayer().name());
    game.watson_next_rolls.emplace(6, 6);
    game.requestRollDice(player_1);

    EXPECT_EQ(roll_spy.size(), 1);
    EXPECT_EQ(move_spy.size(), 1);
    EXPECT_EQ("forward", move_spy.last().at(2).toString().toStdString());
    EXPECT_NE(nullptr, dynamic_cast<MoveState*>(game.state()));

    game.watson_next_rolls.emplace(6, 6);
    game.requestRollDice(player_1);

    EXPECT_EQ(roll_spy.size(), 2);
    EXPECT_EQ(move_spy.size(), 2);
    EXPECT_EQ("forward", move_spy.last().at(2).toString().toStdString());
    EXPECT_NE(nullptr, dynamic_cast<MoveState*>(game.state()));

    game.watson_next_rolls.emplace(6, 6);
    game.requestRollDice(player_1);

    EXPECT_TRUE(game.currentPlayer().inJail());
    EXPECT_EQ(4, game.currentPlayer().position());

    EXPECT_EQ(roll_spy.size(), 3);
    EXPECT_EQ(move_spy.size(), 3);
    EXPECT_EQ("jump", move_spy.last().at(2).toString().toStdString());
    
	EXPECT_NE(nullptr, dynamic_cast<IdleState*>(game.state()));
}

TEST(MoveStateTest, roll_dice_false_player)
{
    Game game;
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.stateChange<MoveState>();

    EXPECT_EQ(player_1, game.currentPlayer().name());
    EXPECT_THROW(game.requestRollDice(player_2), Exception);
}

TEST(MoveStateTest, state_transfer_to_idle)
{
    Game game(std::move(fieldsFree()));

    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.stateChange<MoveState>();

    EXPECT_EQ(player_1, game.currentPlayer().name());
    game.watson_next_rolls.emplace(1, 2);
    game.requestRollDice(player_1);

    EXPECT_NE(nullptr, dynamic_cast<IdleState*>(game.state()));
}

TEST(MoveStateTest, possible_requests)
{
    Game game;
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.stateChange<MoveState>();
    QSignalSpy request_spy(&game, &Game::onPossibleRequests);

    game.requestPossibleRequests(player_1);

    EXPECT_EQ(player_1, game.currentPlayer().name());
    EXPECT_EQ(player_1, request_spy.last().at(0).toString());
    EXPECT_TRUE(containsRequest(request_spy.last().at(1).toJsonArray(), "roll_dice"));

    game.requestPossibleRequests(player_2);

    EXPECT_EQ(request_spy.last().at(0).toString(), player_2);
    EXPECT_FALSE(containsRequest(request_spy.last().at(1).toJsonArray(), "roll_dice"));
}

TEST(MoveStateTest, update_possible_actions)
{
    Game game(std::move(fieldsFree()));

    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    QSignalSpy request_spy(&game, &Game::onPossibleRequests);

    game.stateChange<MoveState>();

    EXPECT_EQ(2, request_spy.size());

    EXPECT_EQ(player_1, game.currentPlayer().name());
    game.requestRollDice(player_1);
}