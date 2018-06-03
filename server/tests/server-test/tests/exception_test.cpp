#include <gmock/gmock.h>

#include <QJsonDocument>
#include <QJsonObject>

#include <utils/exception.h>

TEST(ExceptionTest, construct_default)
{
    Exception except("error message");
    const auto json = except.json();

    auto obj = QJsonDocument::fromJson(json.toUtf8()).object();
    auto error = obj["error"].toObject();

    EXPECT_EQ(error["id"].toInt(), Exception::InvalidRequest);
    EXPECT_EQ(error["message"].toString(), "error message");
}
