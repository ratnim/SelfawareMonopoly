#include <gmock/gmock.h>

#include <game/board/field.h>
#include <QJsonObject>

TEST(FieldTest, get_description)
{
    Field field("Test", FieldType::start);

    auto description = field.description();

    EXPECT_EQ("Test", description["name"].toString().toStdString());
    EXPECT_EQ("start", description["type"].toString().toStdString());
}