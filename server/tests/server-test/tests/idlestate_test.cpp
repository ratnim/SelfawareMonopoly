#include <gmock/gmock.h>

#include <QSignalSpy>

#include <game/game.h>

#include <game/board/street.h>

#include <game/turn/idlestate.h>
#include <game/turn/movestate.h>
#include <game/turn/jailstate.h>

#include <utils/exception.h>

#include <test_utils/helpers.h>

namespace
{
const QString player_1("Heinz");
const QString player_2("Gertrude");
}

TEST(IdleStateTest, end_turn)
{
    Game game;
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.stateChange<IdleState>();

    QSignalSpy turnChange_spy(&game, &Game::onTurnChange);

    EXPECT_EQ(player_1, game.currentPlayer().name());
    game.requestEndTurn(player_1);

    EXPECT_EQ(turnChange_spy.size(), 1);
}

TEST(IdleStateTest, state_transfer_to_roll)
{
    Game game;
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.stateChange<IdleState>();

    EXPECT_EQ(player_1, game.currentPlayer().name());
    game.requestEndTurn(player_1);

    EXPECT_NE(nullptr, dynamic_cast<MoveState*>(game.state()));
    EXPECT_EQ(player_2, game.currentPlayer().name());
}

TEST(IdleStateTest, state_transfer_to_jail)
{
    Game game;
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.stateChange<IdleState>();

    game.players().storage().at(1).jail();

    EXPECT_EQ(player_1, game.currentPlayer().name());
    game.requestEndTurn(player_1);

    EXPECT_EQ(player_2, game.currentPlayer().name());
    EXPECT_NE(nullptr, dynamic_cast<JailState*>(game.state()));
}

TEST(IdleStateTest, possible_requests)
{
    Game game;
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.stateChange<IdleState>();
    QSignalSpy request_spy(&game, &Game::onPossibleRequests);

    game.requestPossibleRequests(player_1);

    EXPECT_EQ(player_1, game.currentPlayer().name());
    EXPECT_EQ(player_1, request_spy.last().at(0).toString());
    EXPECT_TRUE(containsRequest(request_spy.last().at(1).toJsonArray(), "end_turn"));

    game.requestPossibleRequests(player_2);

    EXPECT_EQ(request_spy.last().at(0).toString(), player_2);
    EXPECT_FALSE(containsRequest(request_spy.last().at(1).toJsonArray(), "end_turn"));
}

TEST(IdleStateTest, update_possible_actions)
{
    Game game;
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    QSignalSpy request_spy(&game, &Game::onPossibleRequests);

    game.stateChange<IdleState>();

    EXPECT_EQ(2, request_spy.size());
}

TEST(IdleStateTest, buy_house)
{
    Game game(fieldsTwoGroups());
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1 } });
    game.stateChange<IdleState>();
    game.bank().createAccount(player_1, 1000);

    dynamic_cast<Street*>(game.board()[0])->changeOwner(player_1);
    dynamic_cast<Street*>(game.board()[1])->changeOwner(player_1);

	QSignalSpy property_spy(&game, &Game::onPropertyChange);
	QSignalSpy money_spy(&game, &Game::onMoneyChange);

    game.requestBuyHouse(player_1, 0, true);

	EXPECT_EQ(1, property_spy.size());
    EXPECT_EQ(1, money_spy.size());

	EXPECT_NE(nullptr, dynamic_cast<IdleState*>(game.state()));
}
