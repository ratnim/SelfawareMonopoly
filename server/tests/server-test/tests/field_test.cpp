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

TEST(FieldTypeStringConverterTest, type_to_name)
{
    EXPECT_EQ(FieldType::jail, FieldTypeStringConverter::typeByName("jail"));
	EXPECT_EQ(FieldType::go_to_jail, FieldTypeStringConverter::typeByName("go_to_jail"));
    EXPECT_ANY_THROW(FieldTypeStringConverter::typeByName("not_there"));
}

TEST(FieldTypeStringConverterTest, name_to_type)
{
    EXPECT_EQ("jail", FieldTypeStringConverter::nameByType(FieldType::jail));
    EXPECT_EQ("go_to_jail", FieldTypeStringConverter::nameByType(FieldType::go_to_jail));
    EXPECT_ANY_THROW(FieldTypeStringConverter::nameByType(static_cast<FieldType>(-1)));
}
