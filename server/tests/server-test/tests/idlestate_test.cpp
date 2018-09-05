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
    EXPECT_TRUE(containsRequest(request_spy.last().at(1).toJsonArray(), "construct_building"));

    game.requestPossibleRequests(player_2);

    EXPECT_EQ(request_spy.last().at(0).toString(), player_2);
    EXPECT_FALSE(containsRequest(request_spy.last().at(1).toJsonArray(), "end_turn"));
    EXPECT_FALSE(containsRequest(request_spy.last().at(1).toJsonArray(), "construct_building"));
}

TEST(IdleStateTest, update_possible_actions)
{
    Game game;
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    QSignalSpy request_spy(&game, &Game::onPossibleRequests);

    game.stateChange<IdleState>();

    EXPECT_EQ(2, request_spy.size());
}

TEST(IdleStateTest, buy_houses)
{
    Game game(fieldsTwoGroups());
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1 } });
    game.stateChange<IdleState>();
    game.bank().createAccount(player_1, 1000);

    dynamic_cast<Street*>(game.board()[0])->changeOwner(player_1);
    dynamic_cast<Street*>(game.board()[1])->changeOwner(player_1);

	QSignalSpy property_spy(&game, &Game::onPropertyChange);
	QSignalSpy money_spy(&game, &Game::onMoneyChange);

    game.requestChangeHouses(player_1, {{0,1}, {1,1}});

    EXPECT_EQ(2, property_spy.size());
    EXPECT_EQ(1, money_spy.size());

	EXPECT_NE(nullptr, dynamic_cast<IdleState*>(game.state()));
}

TEST(IdleStateTest, buy_houses_not_enough_money)
{
    Game game(fieldsTwoGroups());
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1 } });
    game.stateChange<IdleState>();
    game.bank().createAccount(player_1, 0);

    dynamic_cast<Street*>(game.board()[0])->changeOwner(player_1);
    dynamic_cast<Street*>(game.board()[1])->changeOwner(player_1);

	QSignalSpy property_spy(&game, &Game::onPropertyChange);
	QSignalSpy money_spy(&game, &Game::onMoneyChange);

    EXPECT_THROW(game.requestChangeHouses(player_1, {{0,1}, {1,1}}), Exception);

    EXPECT_EQ(0, property_spy.size());
    EXPECT_EQ(0, money_spy.size());

	EXPECT_NE(nullptr, dynamic_cast<IdleState*>(game.state()));
}

TEST(IdleStateTest, buy_houses_not_owned)
{
    Game game(fieldsTwoGroups());
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1 } });
    game.stateChange<IdleState>();
    game.bank().createAccount(player_1, 1000);

	QSignalSpy property_spy(&game, &Game::onPropertyChange);
	QSignalSpy money_spy(&game, &Game::onMoneyChange);

    EXPECT_THROW(game.requestChangeHouses(player_1, {{0,1}, {1,1}}), Exception);

    EXPECT_EQ(0, property_spy.size());
    EXPECT_EQ(0, money_spy.size());

	EXPECT_NE(nullptr, dynamic_cast<IdleState*>(game.state()));
}

TEST(IdleStateTest, buy_houses_wrong_groups)
{
    Game game(fieldsTwoGroups());
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1 } });
    game.stateChange<IdleState>();
    game.bank().createAccount(player_1, 1000);

    dynamic_cast<Street*>(game.board()[0])->changeOwner(player_1);
    dynamic_cast<Street*>(game.board()[1])->changeOwner(player_1);
    dynamic_cast<Street*>(game.board()[2])->changeOwner(player_1);
    dynamic_cast<Street*>(game.board()[3])->changeOwner(player_1);

	QSignalSpy property_spy(&game, &Game::onPropertyChange);
	QSignalSpy money_spy(&game, &Game::onMoneyChange);

    EXPECT_THROW(game.requestChangeHouses(player_1, {{0,1}, {2,1}}), Exception);

    EXPECT_EQ(0, property_spy.size());
    EXPECT_EQ(0, money_spy.size());

	EXPECT_NE(nullptr, dynamic_cast<IdleState*>(game.state()));
}

TEST(IdleStateTest, buy_houses_invalid_level)
{
    Game game(fieldsTwoGroups());
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1 } });
    game.stateChange<IdleState>();
    game.bank().createAccount(player_1, 1000);

    dynamic_cast<Street*>(game.board()[0])->changeOwner(player_1);
    dynamic_cast<Street*>(game.board()[1])->changeOwner(player_1);

	QSignalSpy property_spy(&game, &Game::onPropertyChange);
	QSignalSpy money_spy(&game, &Game::onMoneyChange);

    EXPECT_THROW(game.requestChangeHouses(player_1, {{0,1}, {1,42}}), Exception);

    EXPECT_EQ(0, property_spy.size());
    EXPECT_EQ(0, money_spy.size());

	EXPECT_NE(nullptr, dynamic_cast<IdleState*>(game.state()));
}

TEST(IdleStateTest, buy_houses_no_streets)
{
    Game game(fieldsFree());
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1 } });
    game.stateChange<IdleState>();
    game.bank().createAccount(player_1, 1000);

	QSignalSpy property_spy(&game, &Game::onPropertyChange);
	QSignalSpy money_spy(&game, &Game::onMoneyChange);

    EXPECT_THROW(game.requestChangeHouses(player_1, {{0,1}, {1,1}}), Exception);

    EXPECT_EQ(0, property_spy.size());
    EXPECT_EQ(0, money_spy.size());

	EXPECT_NE(nullptr, dynamic_cast<IdleState*>(game.state()));
}

TEST(IdleStateTest, sell_houses)
{
    Game game(fieldsTwoGroups());
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1 } });
    game.stateChange<IdleState>();
    game.bank().createAccount(player_1, 0);

    dynamic_cast<Street*>(game.board()[0])->changeOwner(player_1);
    dynamic_cast<Street*>(game.board()[0])->changeConstructionLevel(ConstructionLevel::HOUSE_1);
    dynamic_cast<Street*>(game.board()[1])->changeOwner(player_1);
    dynamic_cast<Street*>(game.board()[1])->changeConstructionLevel(ConstructionLevel::HOUSE_1);

	QSignalSpy property_spy(&game, &Game::onPropertyChange);
	QSignalSpy money_spy(&game, &Game::onMoneyChange);

    game.requestChangeHouses(player_1, {{0,0}, {1,0}});

    EXPECT_EQ(2, property_spy.size());
    EXPECT_EQ(1, money_spy.size());

	EXPECT_NE(nullptr, dynamic_cast<IdleState*>(game.state()));
}

TEST(IdleStateTest, buy_sell_houses_neutral_cashflow)
{
    Game game(fieldsTwoGroups());
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1 } });
    game.stateChange<IdleState>();
    game.bank().createAccount(player_1, 0);

    // Please ignore that the original configuration is invalid
    dynamic_cast<Street*>(game.board()[0])->changeOwner(player_1);
    dynamic_cast<Street*>(game.board()[0])->changeConstructionLevel(ConstructionLevel::HOUSE_2);
    dynamic_cast<Street*>(game.board()[1])->changeOwner(player_1);

	QSignalSpy property_spy(&game, &Game::onPropertyChange);
	QSignalSpy money_spy(&game, &Game::onMoneyChange);

    // Sell 2, buy 1, each priced 50 -> chashflow = 0
    game.requestChangeHouses(player_1, {{0,0}, {1,1}});

    EXPECT_EQ(2, property_spy.size());
    EXPECT_EQ(0, money_spy.size());

	EXPECT_NE(nullptr, dynamic_cast<IdleState*>(game.state()));
}

TEST(IdleStateTest, buy_sell_houses_no_change)
{
    Game game(fieldsTwoGroups());
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1 } });
    game.stateChange<IdleState>();
    game.bank().createAccount(player_1, 0);

    dynamic_cast<Street*>(game.board()[0])->changeOwner(player_1);
    dynamic_cast<Street*>(game.board()[1])->changeOwner(player_1);

	QSignalSpy property_spy(&game, &Game::onPropertyChange);
	QSignalSpy money_spy(&game, &Game::onMoneyChange);

    game.requestChangeHouses(player_1, {{0,0}, {1,0}});

    EXPECT_EQ(0, property_spy.size());
    EXPECT_EQ(0, money_spy.size());

	EXPECT_NE(nullptr, dynamic_cast<IdleState*>(game.state()));
}
