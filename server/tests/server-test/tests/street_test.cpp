#include <gmock/gmock.h>

#include <QJsonArray>
#include <QJsonObject>

#include <game/game.h>
#include <game/turn/buystate.h>

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

TEST(StreetTest, transfer_to_states)
{
    Game game;
    Street street("Test", 5, 200, 50, { 24, 120, 360, 850, 1025, 1200 });
    EXPECT_TRUE(street.moveOn("Gertrude", &game));
    EXPECT_NE(nullptr, dynamic_cast<BuyState*>(game.state()));

    street.changeOwner("Gertrude");
    EXPECT_FALSE(street.moveOn("Gertrude", &game));
    EXPECT_FALSE(street.moveOn("Herbert", &game));
}
