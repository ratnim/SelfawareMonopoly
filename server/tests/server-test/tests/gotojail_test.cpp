#include <gmock/gmock.h>

#include <QJsonArray>
#include <QJsonObject>

#include <game/board/gotojail.h>

TEST(GoToJailTest, get_description)
{
    GoToJail gotojail("Go To Jail");

    auto description = gotojail.description();

    EXPECT_EQ("Go To Jail", description["name"].toString().toStdString());
    EXPECT_EQ("go_to_jail", description["type"].toString().toStdString());
}