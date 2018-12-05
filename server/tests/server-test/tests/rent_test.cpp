#include <gmock/gmock.h>

#include <QJsonObject>
#include <QJsonArray>

#include <game/board/fieldfactory.h>
#include <game/board/board.h>
#include <game/board/street.h>

// reaching fault, producing an error and leading to failure
TEST(RentTest, rent_street_group_1)
{
    const uint16_t default_rent = 24;
    QJsonObject specification{
            { "name", "TestStreet" },
            { "type", "street" },
            { "group", 5 },
            { "price", 280 },
            { "house_price", 150 },
            { "rent", QJsonArray({default_rent, 120, 360, 850, 1025, 1200}) }
    };

    auto builtField = FieldFactory::create(specification);

    std::vector<std::unique_ptr<Field>> fields;
    fields.push_back(std::move(builtField));
    Board board(std::move(fields));

    auto street = dynamic_cast<Street*>(board[0]);
    EXPECT_EQ(default_rent*2, street->rent(board, 0));
}

// reaching fault, not producing an error
TEST(RentTest, rent_street_group_2)
{
    const uint16_t default_rent = 0;
    QJsonObject specification{
            { "name", "TestStreet" },
            { "type", "street" },
            { "group", 5 },
            { "price", 280 },
            { "house_price", 150 },
            { "rent", QJsonArray({default_rent, 120, 360, 850, 1025, 1200}) }
    };

    auto builtField = FieldFactory::create(specification);

    std::vector<std::unique_ptr<Field>> fields;
    fields.push_back(std::move(builtField));
    Board board(std::move(fields));

    auto street = dynamic_cast<Street*>(board[0]);
    EXPECT_EQ(default_rent*2, street->rent(board, 0));
}