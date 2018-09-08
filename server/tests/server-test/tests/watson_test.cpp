#include <gmock/gmock.h>

#include <QSignalSpy>

#include <game/game.h>
#include <game/turn/movestate.h>
#include <game/watson.h>

#include <utils/exception.h>

#include <test_utils/helpers.h>

namespace
{
const QString player_1("Heinz");
const QString player_2("Gertrude");
}

TEST(WatsonTest, manipulate_dices)
{
    Game game(std::move(fieldsFree()));

    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.stateChange<MoveState>();

    QSignalSpy roll_spy(&game, &Game::onRollDice);

    game.watson().doManipulateNextRoll(player_1, { 6, 6 });

    game.requestRollDice(player_1);

    EXPECT_EQ(6, roll_spy.last().at(1).toInt());
    EXPECT_EQ(6, roll_spy.last().at(2).toInt());
}

TEST(WatsonTest, harm_player_on_request_add_click)
{
    Game game(std::move(fieldsTax()));

    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.stateChange<MoveState>();

    QSignalSpy roll_spy(&game, &Game::onRollDice);

    game.watson().requestAddClick(player_2, "test_add");

    game.requestRollDice(player_1);

    EXPECT_EQ(5, roll_spy.last().at(1).toInt() + roll_spy.last().at(2).toInt());
}

TEST(WatsonTest, harm_player_on_request_not_overrides)
{
    Game game(std::move(fieldsTax()));

    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.stateChange<MoveState>();

    QSignalSpy roll_spy(&game, &Game::onRollDice);

    game.watson().doManipulateNextRoll(player_1, 1, 2);

    game.watson().requestAddClick(player_2, "test_add");

    game.requestRollDice(player_1);

    EXPECT_EQ(3, roll_spy.last().at(1).toInt() + roll_spy.last().at(2).toInt());
}

TEST(WatsonTest, scan_gmail)
{
    Game game(std::move(fieldsTax()));

    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.stateChange<MoveState>();

    QSignalSpy roll_spy(&game, &Game::onRollDice);

    game.watson().requestScannedGMailAccount(player_1, { 1, 2 });

    game.requestRollDice(player_1);

    EXPECT_EQ(3, roll_spy.last().at(1).toInt() + roll_spy.last().at(2).toInt());
}

TEST(WatsonTest, scan_gmail_overrides)
{
    Game game(std::move(fieldsTax()));

    game.players() = RingBuffer<Player>(std::vector<Player>{ { player_1, player_2 } });
    game.stateChange<MoveState>();

    QSignalSpy roll_spy(&game, &Game::onRollDice);

    game.watson().doManipulateNextRoll(player_1, 1, 2);

    game.watson().requestScannedGMailAccount(player_1, { 2, 3 });

    game.requestRollDice(player_1);

    EXPECT_EQ(5, roll_spy.last().at(1).toInt() + roll_spy.last().at(2).toInt());
}

TEST(WatsonTest, coins_to_money)
{
    EXPECT_EQ(50, Watson::coinsToMoney(1));
    EXPECT_EQ(150, Watson::coinsToMoney(3));
}

TEST(WatsonTest, coins_for_money_needed)
{
    EXPECT_EQ(1, Watson::coinsForMoneyNeeded(1));
    EXPECT_EQ(1, Watson::coinsForMoneyNeeded(49));
    EXPECT_EQ(1, Watson::coinsForMoneyNeeded(50));
    EXPECT_EQ(2, Watson::coinsForMoneyNeeded(51));
}

TEST(WatsonTest, money_for_coins_available)
{
    Game game;

    EXPECT_EQ(0, game.watson().availableMoneyForCoins(player_1));
    game.watson().doAddWatsonCoins(player_1, 1);
    EXPECT_EQ(50, game.watson().availableMoneyForCoins(player_1));

    game.watson().doAddWatsonCoins(player_2, 3);
    EXPECT_EQ(150, game.watson().availableMoneyForCoins(player_2));
}

TEST(WatsonTest, use_money_for_coins)
{
    Game game;

    game.watson().doAddWatsonCoins(player_1, 4);
    game.watson().doUseCoinsForMoney(player_1, 50);

    EXPECT_EQ(150, game.watson().availableMoneyForCoins(player_1));

    game.watson().doUseCoinsForMoney(player_1, 75);

    EXPECT_EQ(50, game.watson().availableMoneyForCoins(player_1));

    EXPECT_THROW(game.watson().doUseCoinsForMoney(player_1, 100), Exception);
    EXPECT_EQ(50, game.watson().availableMoneyForCoins(player_1));
}
