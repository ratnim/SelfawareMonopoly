#include <gmock/gmock.h>

#include <QJsonObject>
#include <QJsonArray>

#include <game/board/fieldfactory.h>
#include <game/board/street.h>
#include <game/board/gotojail.h>

TEST(FieldFactoryTest, construct_field_start)
{
    QJsonObject specification{
        { "name", "Start" },
        { "type", "start" }
    };

    auto field = FieldFactory::create(specification);

    EXPECT_EQ(FieldType::start, field->type());
    EXPECT_EQ("Start", field->name());
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

    auto field = FieldFactory::create(specification);

    EXPECT_EQ("TestStreet", field->name());
    EXPECT_EQ(FieldType::street, field->type());

	auto street = dynamic_cast<Street*>(field.get());
    EXPECT_NE(nullptr, street);
    EXPECT_EQ(5, street->group());
    EXPECT_EQ(280, street->price());
    EXPECT_EQ(150, street->housePrice());
    EXPECT_EQ(24, street->rent());
}

TEST(FieldFactoryTest, construct_field_station)
{
    QJsonObject specification{
        { "name", "TestStation" },
        { "type", "station" }
    };

    auto field = FieldFactory::create(specification);

    EXPECT_EQ(FieldType::station, field->type());
    EXPECT_EQ("TestStation", field->name());
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
        { "type", "tax" }
    };

    auto field = FieldFactory::create(specification);

    EXPECT_EQ(FieldType::tax, field->type());
    EXPECT_EQ("TestTax", field->name());
}

TEST(FieldFactoryTest, construct_field_utility)
{
    QJsonObject specification{
        { "name", "TestUtility" },
        { "type", "utility" }
    };

    auto field = FieldFactory::create(specification);

    EXPECT_EQ(FieldType::utility, field->type());
    EXPECT_EQ("TestUtility", field->name());
}
