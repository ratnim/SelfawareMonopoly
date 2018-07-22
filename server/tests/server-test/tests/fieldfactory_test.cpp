#include <gmock/gmock.h>

#include <QJsonObject>;

#include <game/board/fieldfactory.h>

TEST(FieldFactoryTest, construct_field_start)
{
    QJsonObject specification{
        { "name", "Start" },
        { "type",  "start"}
    };

    auto field = FieldFactory::create(specification);

	EXPECT_EQ(FieldType::Start, field.type());
    EXPECT_EQ("Start", field.name());
}
