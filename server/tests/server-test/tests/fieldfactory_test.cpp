#include <gmock/gmock.h>

#include <QJsonObject>
#include <QJsonArray>

#include <game/board/fieldfactory.h>
#include <game/board/board.h>
#include <game/board/street.h>
#include <game/board/station.h>
#include <game/board/utility.h>
#include <game/board/gotojail.h>
#include <game/board/start.h>
#include <game/board/taxfield.h>

TEST(FieldFactoryTest, construct_field_start)
{
    QJsonObject specification{
        { "name", "Start" },
        { "type", "start" }
    };

    auto field = FieldFactory::create(specification);
    auto start = dynamic_cast<Start*>(field.get());
    EXPECT_NE(nullptr, start);
    EXPECT_EQ(FieldType::start, start->type());
    EXPECT_EQ("Start", start->name());
}

TEST(FieldFactoryTest, construct_field_street)
{
    QJsonObject specification{
        { "name", "TestStreet" },
        { "type", "street" },
        { "group", 5 },
        { "price", 280 },
        { "house_price", 150 },
        { "rent", QJsonArray({24, 120, 360, 850, 1025, 1200}) }
    };

    auto builtField = FieldFactory::create(specification);

    // We need a board to check the rent
    std::vector<std::unique_ptr<Field>> fields;
    fields.push_back(std::move(builtField));
    Board board(std::move(fields));

    auto field = board[0];

    EXPECT_EQ("TestStreet", field->name());
    EXPECT_EQ(FieldType::street, field->type());

    auto street = dynamic_cast<Street*>(field);
    EXPECT_NE(nullptr, street);
    EXPECT_EQ(5, street->group());
    EXPECT_EQ(280, street->price());
    EXPECT_EQ(150, street->housePrice());
    EXPECT_EQ(24 * 2, street->rent(board, 0)); // Double rent rule applies
}

TEST(FieldFactoryTest, construct_field_station)
{
    QJsonObject specification{
        { "name", "TestStation" },
        { "type", "station" },
        { "group", 5 },
        { "price", 280 },
        { "rent", QJsonArray{{24}} }
    };

    auto builtField = FieldFactory::create(specification);

    // We need a board to check the rent
    std::vector<std::unique_ptr<Field>> fields;
    fields.push_back(std::move(builtField));
    Board board(std::move(fields));

    auto field = board[0];

    EXPECT_EQ("TestStation", field->name());
    EXPECT_EQ(FieldType::station, field->type());

    auto station = dynamic_cast<Station*>(field);
    EXPECT_NE(nullptr, station);
    EXPECT_EQ(5, station->group());
    EXPECT_EQ(280, station->price());
    EXPECT_EQ(24, station->rent(board, 0));
}

TEST(FieldFactoryTest, construct_field_event_card)
{
    QJsonObject specification{
        { "name", "TestEventCard" },
        { "type", "event_card" }
    };

    auto field = FieldFactory::create(specification);

    EXPECT_EQ(FieldType::event_card, field->type());
    EXPECT_EQ("TestEventCard", field->name());
}

TEST(FieldFactoryTest, construct_field_society_card)
{
    QJsonObject specification{
        { "name", "TestSocietyCard" },
        { "type", "society_card" }
    };

    auto field = FieldFactory::create(specification);

    EXPECT_EQ(FieldType::society_card, field->type());
    EXPECT_EQ("TestSocietyCard", field->name());
}

TEST(FieldFactoryTest, construct_field_prison)
{
    QJsonObject specification{
        { "name", "Jail" },
        { "type", "jail" }
    };

    auto field = FieldFactory::create(specification);

    EXPECT_EQ(FieldType::jail, field->type());
    EXPECT_EQ("Jail", field->name());
}

TEST(FieldFactoryTest, construct_field_free_parking)
{
    QJsonObject specification{
        { "name", "Free Parking" },
        { "type", "free" }
    };

    auto field = FieldFactory::create(specification);

    EXPECT_EQ(FieldType::free, field->type());
    EXPECT_EQ("Free Parking", field->name());
}

TEST(FieldFactoryTest, construct_field_go_to_jail)
{
    QJsonObject specification{
        { "name", "Go to Jail" },
        { "type", "go_to_jail" }
    };

    auto field = FieldFactory::create(specification);
    auto gotojail = dynamic_cast<GoToJail*>(field.get());

    EXPECT_NE(nullptr, gotojail);
    EXPECT_EQ(FieldType::go_to_jail, field->type());
    EXPECT_EQ("Go to Jail", field->name());
}

TEST(FieldFactoryTest, construct_field_tax)
{
    QJsonObject specification{
        { "name", "TestTax" },
        { "type", "tax" },
        { "rent", QJsonArray{{100}} }
    };

    auto field = FieldFactory::create(specification);
    auto tax = dynamic_cast<TaxField*>(field.get());

    ASSERT_NE(nullptr, tax);
    EXPECT_EQ(FieldType::tax, field->type());
    EXPECT_EQ("TestTax", field->name());
    EXPECT_EQ(100, tax->amount());
}

TEST(FieldFactoryTest, construct_field_utility)
{
    QJsonObject specification{
        { "name", "TestStation" },
        { "type", "utility" },
        { "group", 5 },
        { "price", 280 },
        { "rent", QJsonArray({2, 4}) }
    };

    auto builtField = FieldFactory::create(specification);

    // We need a board to check the rent
    std::vector<std::unique_ptr<Field>> fields;
    fields.push_back(std::move(builtField));
    Board board(std::move(fields));

    auto field = board[0];

    EXPECT_EQ("TestStation", field->name());
    EXPECT_EQ(FieldType::utility, field->type());

    auto util = dynamic_cast<Utility*>(field);
    EXPECT_NE(nullptr, util);
    EXPECT_EQ(5, util->group());
    EXPECT_EQ(280, util->price());
    EXPECT_EQ(2, util->rent(board, 1));
    EXPECT_EQ(4, util->rent(board, 2));
}
