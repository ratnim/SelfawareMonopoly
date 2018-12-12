#include <gmock/gmock.h>

#include <QJsonObject>
#include <QJsonArray>

#include <game/board/fieldfactory.h>
#include <game/board/board.h>
#include <game/board/street.h>

/*** Input Domain Modeling test cases
 *
 *  used coverage criterion: base choice
 *  characteristics:
 *      - q1 = rent multiplication {single, double}
 *      - q2 = rent value {less than 0, equal to 0, greater than 0}
 *
 *  base choice blocks:
 *      - q1 = single, q2 = greater than 0
 *
 * base choice combinations:
 *      - q1 = single, q2 = greater than 0
 *      - q1 = single, q2 = less than 0
 *      - q1 = single, q2 = equal to 0
 *      - q1 = double, q2 = greater than 0
 *      - q1 = double, q2 = less than 0
 *      - q1 = double, q2 = equal to 0
 */


// case 1
// rent multiplication  = single
// rent                 = greater than 0
TEST(RentTestIDM, rent_street_idm_01)
{
    const int16_t default_rent = 1;
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
    // street owner is not street group owner
    street->changeOwner(QString{"Other"});
    EXPECT_EQ(default_rent, street->rent(board, 0));
}

// case 2
// rent multiplication  = single
// rent                 = less than 0
TEST(RentTestIDM, rent_street_idm_02)
{
    const int16_t default_rent = -1;
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
    // street owner is not street group owner
    street->changeOwner(QString{"Other"});
    EXPECT_EQ(default_rent, street->rent(board, 0));
}

// case 3
// rent multiplication  = single
// rent                 = equal to 0
TEST(RentTestIDM, rent_street_idm_03)
{
    const int16_t default_rent = 0;
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
    street->changeOwner(QString{"Other"});
    EXPECT_EQ(default_rent, street->rent(board, 0));
}

// case 4
// rent multiplication  = double
// rent                 = greater than 0
TEST(RentTestIDM, rent_street_idm_04)
{
    const int16_t default_rent = 1;
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
    street->changeOwner(QString{"Other"});
    EXPECT_EQ(2*default_rent, street->rent(board, 0));
}

// case 5
// rent multiplication  = double
// rent                 = less than 0
TEST(RentTestIDM, rent_street_idm_05)
{
    const int16_t default_rent = -1;
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
    street->changeOwner(QString{"Other"});
    EXPECT_EQ(2*default_rent, street->rent(board, 0));
}

// case 6
// rent multiplication  = single
// rent                 = equal to 0
TEST(RentTestIDM, rent_street_idm_06)
{
    const int16_t default_rent = 0;
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
    street->changeOwner(QString{"Other"});
    EXPECT_EQ(2*default_rent, street->rent(board, 0));
}