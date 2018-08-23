#include <gmock/gmock.h>

#include <QJsonObject>

#include <game/board/fieldfactory.h>
#include <game/board/street.h>

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
        { "type", "street" }
    };

    auto field = FieldFactory::create(specification);

    EXPECT_EQ(FieldType::street, field->type());
    EXPECT_EQ("TestStreet", field->name());

    auto a = new Field("a", FieldType::street);
    auto street = dynamic_cast<Street *>(a);
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

TEST(FieldFactoryTest, construct_field_go_to_prison)
{
    QJsonObject specification{
        { "name", "Go to Jail" },
        { "type", "go_to_jail" }
    };

    auto field = FieldFactory::create(specification);

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
