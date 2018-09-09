#include <gmock/gmock.h>

#include <QJsonArray>
#include <QJsonObject>

#include <game/game.h>
#include <game/turn/paystate.h>

#include <game/board/taxfield.h>

TEST(TaxFieldTest, get_description)
{
    TaxField tax("Test", 100);

    auto description = tax.description();

    EXPECT_EQ("Test", description["name"].toString().toStdString());
    EXPECT_EQ("tax", description["type"].toString().toStdString());
    EXPECT_EQ(100, description["amount"].toInt());
}

TEST(TaxFieldTest, transfer_to_pay_state)
{
    Game game;
    TaxField tax("Test", 100);
    EXPECT_TRUE(tax.moveOn("Gertrude", &game, 0));
    EXPECT_NE(nullptr, dynamic_cast<PayState*>(game.state()));
}
