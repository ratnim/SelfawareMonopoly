#include <gmock/gmock.h>

#include <QJsonDocument>
#include <QJsonObject>

#include <utils/exception.h>

TEST(ExceptionTest, construct_simple)
{
    Exception except("error message");
    const auto json = except.json();

    auto obj = QJsonDocument::fromJson(json.toUtf8()).object();
    auto error = obj["error"].toObject();

    EXPECT_EQ(error["id"].toInt(), Exception::InvalidRequest);
    EXPECT_EQ(error["message"].toString(), "error message");
}

TEST(ExceptionTest, api_compatibility)
{
    EXPECT_EQ(Exception::error::NoError, 0);
    EXPECT_EQ(Exception::error::InvalidRoute, 1);
    EXPECT_EQ(Exception::error::UnsupportedAction, 2);
    EXPECT_EQ(Exception::error::MalformedRequest, 3);
    EXPECT_EQ(Exception::error::InvalidRequest, 4);
    EXPECT_EQ(Exception::error::InternalError, 5);
}
