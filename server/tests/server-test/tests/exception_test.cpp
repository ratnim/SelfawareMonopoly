#include <gmock/gmock.h>

#include <QJsonDocument>
#include <QJsonObject>

#include <utils/exception.h>

TEST(ExceptionTest, construct_simple)
{
    Exception except("error message");
    const auto json = except.json();

    auto obj = QJsonDocument::fromJson(json.toUtf8()).object();
    auto err = obj["data"].toObject();

    EXPECT_EQ(obj["name"].toString().toStdString(), "error");
    EXPECT_EQ(err["id"].toInt(), Error::InvalidRequest);
    EXPECT_EQ(err["message"].toString().toStdString(), "InvalidRequest: error message");
}

TEST(ExceptionTest, api_compatibility)
{
    EXPECT_EQ(Error::NoError, 0);
    EXPECT_EQ(Error::InvalidRoute, 1);
    EXPECT_EQ(Error::UnsupportedAction, 2);
    EXPECT_EQ(Error::MalformedRequest, 3);
    EXPECT_EQ(Error::InvalidRequest, 4);
    EXPECT_EQ(Error::InternalError, 5);
}
