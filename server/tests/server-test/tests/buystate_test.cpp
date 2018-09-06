#include <gmock/gmock.h>

#include <QSignalSpy>

#include <game/game.h>

#include <game/turn/buystate.h>
#include <game/turn/idlestate.h>
#include <game/turn/movestate.h>

#include <utils/exception.h>

#include <test_utils/helpers.h>

namespace
{
const QString player_1("Heinz");
const QString player_2("Gertrude");
}

TEST(BuyStateTest, buy_street)
{
    Game game(fieldsStreets());
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.stateChange<BuyState>();
    game.bank().createAccount(game.currentPlayer().name(), 1000);

	QSignalSpy property_spy(&game, &Game::onPropertyChange);
	QSignalSpy money_spy(&game, &Game::onMoneyChange);

	game.requestBuyField(game.currentPlayer().name(), true);

	EXPECT_EQ(1, property_spy.size());
    EXPECT_EQ(1, money_spy.size());

	EXPECT_NE(nullptr, dynamic_cast<MoveState*>(game.state()));
}

TEST(BuyStateTest, dont_buy_street)
{
    Game game(fieldsStreets());
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.stateChange<BuyState>();
    game.bank().createAccount(game.currentPlayer().name(), 1000);

    QSignalSpy property_spy(&game, &Game::onPropertyChange);
    QSignalSpy money_spy(&game, &Game::onMoneyChange);

    game.requestBuyField(game.currentPlayer().name(), false);

    EXPECT_EQ(0, property_spy.size());
    EXPECT_EQ(0, money_spy.size());

    EXPECT_NE(nullptr, dynamic_cast<MoveState*>(game.state()));
}

TEST(BuyStateTest, buy_street_not_enough_money)
{
    Game game(fieldsStreets());
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.stateChange<BuyState>();
    game.bank().createAccount(game.currentPlayer().name(), 0);

    QSignalSpy property_spy(&game, &Game::onPropertyChange);
    QSignalSpy money_spy(&game, &Game::onMoneyChange);

    EXPECT_THROW(game.requestBuyField(game.currentPlayer().name(), true), Exception);

    EXPECT_EQ(0, property_spy.size());
    EXPECT_EQ(0, money_spy.size());

    EXPECT_NE(nullptr, dynamic_cast<BuyState*>(game.state()));
}


TEST(BuyStateTest, possible_requests)
{
    Game game(fieldsStreets());
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.stateChange<BuyState>();
    QSignalSpy request_spy(&game, &Game::onPossibleRequests);

    game.requestPossibleRequests(player_1);

    EXPECT_EQ(player_1, game.currentPlayer().name());
    EXPECT_EQ(player_1, request_spy.last().at(0).toString());
    EXPECT_TRUE(containsRequest(request_spy.last().at(1).toJsonArray(), "dont_buy_field"));
    EXPECT_TRUE(containsRequest(request_spy.last().at(1).toJsonArray(), "buy_field"));

    game.requestPossibleRequests(player_2);

    EXPECT_EQ(request_spy.last().at(0).toString(), player_2);
    EXPECT_FALSE(containsRequest(request_spy.last().at(1).toJsonArray(), "dont_buy_field"));
    EXPECT_FALSE(containsRequest(request_spy.last().at(1).toJsonArray(), "buy_field"));
}

TEST(BuyStateTest, update_possible_requests)
{
    Game game(fieldsStreets());
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    QSignalSpy request_spy(&game, &Game::onPossibleRequests);

    game.stateChange<BuyState>();

    EXPECT_EQ(2, request_spy.size());
}