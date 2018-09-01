#include <gmock/gmock.h>

#include <QSignalSpy>

#include <game/game.h>

#include <game/turn/paystate.h>
#include <game/turn/movestate.h>

#include <test_utils/helpers.h>

namespace
{
const QString player_1("Heinz");
const QString player_2("Gertrude");
}

TEST(PayStateTest, possible_requests)
{
    Game game;
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    std::vector<Debt> debts;
    debts.emplace_back(player_1, player_2, 100);
    game.stateChange<PayState>(debts);
    QSignalSpy request_spy(&game, &Game::onPossibleRequests);

    game.requestPossibleRequests(player_1);

    EXPECT_EQ(player_1, game.currentPlayer().name());
    EXPECT_EQ(player_1, request_spy.last().at(0).toString());
    EXPECT_TRUE(containsRequest(request_spy.last().at(1).toJsonArray(), "pay_debt"));

    game.requestPossibleRequests(player_2);

    EXPECT_EQ(request_spy.last().at(0).toString(), player_2);
    EXPECT_FALSE(containsRequest(request_spy.last().at(1).toJsonArray(), "pay_debt"));
}

TEST(PayStateTest, update_possible_requests)
{
    Game game;

    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    QSignalSpy request_spy(&game, &Game::onPossibleRequests);

    std::vector<Debt> debts;
    debts.emplace_back(player_1, player_2, 100);

    game.stateChange<PayState>(debts);

    EXPECT_EQ(2, request_spy.size());
}

TEST(PayStateTest, pay_debt)
{
    Game game;
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.bank().createAccount(player_1, 100);
    game.bank().createAccount(player_2, 0);
	std::vector<Debt> debts;
    debts.emplace_back(player_1, player_2, 100);
    game.stateChange<PayState>(debts);

    QSignalSpy money_spy(&game, &Game::onMoneyChange);

	game.requestPayDebt(player_1, player_2);

	EXPECT_EQ(2, money_spy.size());
	EXPECT_NE(nullptr, dynamic_cast<MoveState*>(game.state()));

	EXPECT_EQ(0, game.bank().balance(player_1));
	EXPECT_EQ(100, game.bank().balance(player_2));
}
