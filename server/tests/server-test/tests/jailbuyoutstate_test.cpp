#include <gmock/gmock.h>

#include <QSignalSpy>

#include <models/boardmodel.h>

#include <game/game.h>

#include <game/turn/jailstate.h>
#include <game/turn/jailbuyoutstate.h>

#include <utils/exception.h>

#include <test_utils/helpers.h>

namespace
{
const QString player_1("Heinz");
const QString player_2("Gertrude");
}

TEST(JailBuyoutStateTest, possible_requests)
{
    Game game;
    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    QSignalSpy request_spy(&game, &Game::onPossibleRequests);
    game.doCurrentPlayerGoToJail();
    game.stateChange<JailBuyoutState>(Dices{1,2});

    // Case 1: First or second try
    game.requestPossibleRequests(player_1);

    EXPECT_EQ(player_1, game.currentPlayer().name());
    EXPECT_EQ(player_1, request_spy.last().at(0).toString());
    EXPECT_TRUE(containsRequest(request_spy.last().at(1).toJsonArray(), "pay_debt"));
    EXPECT_TRUE(containsRequest(request_spy.last().at(1).toJsonArray(), "end_turn"));

    // Let the player roll 3 times
    game.currentPlayer().rolled();
    game.currentPlayer().rolled();
    game.currentPlayer().rolled();

    // Case 2: Third try
    game.requestPossibleRequests(player_1);

    EXPECT_EQ(player_1, game.currentPlayer().name());
    EXPECT_EQ(player_1, request_spy.last().at(0).toString());
    EXPECT_TRUE(containsRequest(request_spy.last().at(1).toJsonArray(), "pay_debt"));
    EXPECT_FALSE(containsRequest(request_spy.last().at(1).toJsonArray(), "end_turn"));

    // Other players
    game.requestPossibleRequests(player_2);

    EXPECT_EQ(request_spy.last().at(0).toString(), player_2);
    EXPECT_FALSE(containsRequest(request_spy.last().at(1).toJsonArray(), "pay_debt"));
    EXPECT_FALSE(containsRequest(request_spy.last().at(1).toJsonArray(), "end_turn"));
}
