#include <gmock/gmock.h>

#include <vector>
#include <memory>


#include <QJsonArray>
#include <QJsonObject>

#include <game/board/board.h>

TEST(BoardTest, get_description)
{
    std::vector<std::unique_ptr<Field>>fields;
    fields.push_back(std::move(std::make_unique<Field>("first", FieldType::start)));
    fields.push_back(std::move(std::make_unique<Field>("second", FieldType::jail)));
    Board board(std::move(fields));
    auto description = board.description();

    EXPECT_EQ(2, description["fields"].toArray().size());
    EXPECT_EQ("first", description["fields"].toArray()[0].toObject()["name"].toString().toStdString());
    EXPECT_EQ("second", description["fields"].toArray()[1].toObject()["name"].toString().toStdString());
}
