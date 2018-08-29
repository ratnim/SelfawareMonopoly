#include <gmock/gmock.h>

#include <QJsonObject>
#include <QJsonArray>

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