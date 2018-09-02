#include <gmock/gmock.h>

#include <QJsonArray>
#include <QJsonObject>

#include <game/game.h>
#include <game/turn/buystate.h>
#include <game/turn/initstate.h>
#include <game/turn/paystate.h>

#include <game/board/street.h>

TEST(StreetTest, get_description)
{
    Street street("Test", 5, 200, 50, { 24, 120, 360, 850, 1025, 1200 });

    auto description = street.description();

    EXPECT_EQ("Test", description["name"].toString().toStdString());
    EXPECT_EQ("street", description["type"].toString().toStdString());
    EXPECT_EQ(5, description["group"].toInt());
    EXPECT_EQ(200, description["price"].toInt());
    EXPECT_EQ(50, description["house_price"].toInt());
    EXPECT_EQ(QJsonArray({ 24, 120, 360, 850, 1025, 1200 }), description["rent"].toArray());
}

TEST(StreetTest, transfer_to_buy_state)
{
    Game game;
    Street street("Test", 5, 200, 50, { 24, 120, 360, 850, 1025, 1200 });
    EXPECT_TRUE(street.moveOn("Gertrude", &game));
    EXPECT_NE(nullptr, dynamic_cast<BuyState*>(game.state()));
}

TEST(StreetTest, transfer_to_pay_state)
{
    Game game;
    Street street("Test", 5, 200, 50, { 24, 120, 360, 850, 1025, 1200 });
    street.changeOwner("Gertrude");

    EXPECT_TRUE(street.moveOn("Herbert", &game));
    EXPECT_NE(nullptr, dynamic_cast<PayState*>(game.state()));
}

TEST(StreetTest, dont_change_state)
{
    Game game;
    Street street("Test", 5, 200, 50, { 24, 120, 360, 850, 1025, 1200 });
    street.changeOwner("Gertrude");

    EXPECT_FALSE(street.moveOn("Gertrude", &game));
    EXPECT_NE(nullptr, dynamic_cast<InitState*>(game.state()));
}
