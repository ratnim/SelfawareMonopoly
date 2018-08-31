#include <gmock/gmock.h>

#include <QSignalSpy>

#include <game/game.h>

#include <game/turn/paystate.h>

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

    EXPECT_EQ(player_1, game.currentPlayer().name());
    game.requestRollDice(player_1);
}
