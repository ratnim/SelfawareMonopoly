#include <gmock/gmock.h>

#include <QJsonDocument>

#include <mocked_server.h>
#include <overview.h>

class OveviewTest : public ::testing::Test, public Overview
{
};

TEST_F(OveviewTest, unsupported_action)
{
    QJsonObject request;
    request["request"] = "something";
    auto answer = handle(request);
    QJsonObject obj = QJsonDocument::fromJson(answer.toUtf8()).object();

    EXPECT_EQ(obj["error"].toObject()["id"].toInt(), Route::UnsupportedAction);
}

TEST_F(OveviewTest, invalid_request_no_data)
{
    QJsonObject request;
    request["request"] = "enter_lobby";

    auto answer = handle(request);
    QJsonObject obj = QJsonDocument::fromJson(answer.toUtf8()).object();

    EXPECT_EQ(obj["error"].toObject()["id"].toInt(), Route::InvalidRequest);
}

TEST_F(OveviewTest, invalid_request_no_player_name)
{
    QJsonObject request;
    request["request"] = "enter_lobby";
    request["data"] = QJsonObject();

    auto answer = handle(request);
    QJsonObject obj = QJsonDocument::fromJson(answer.toUtf8()).object();

    EXPECT_EQ(obj["error"].toObject()["id"].toInt(), Route::InvalidRequest);
}

TEST_F(OveviewTest, user_error_player_name_taken)
{
    EXPECT_TRUE(createUser("test_user", createSession()));

    QJsonObject request;
    request["request"] = "enter_lobby";
    QJsonObject data;
    data["player_name"] = "test_user";
    request["data"] = data;

    auto answer = handle(request);
    QJsonObject obj = QJsonDocument::fromJson(answer.toUtf8()).object();

    EXPECT_EQ(obj["error"].toObject()["id"].toInt(), Route::UserError);
}

TEST_F(OveviewTest, correct_request)
{
    QJsonObject request;
    request["request"] = "enter_lobby";
    QJsonObject data;
    data["player_name"] = "valid_user";
    request["data"] = data;

    auto answer = handle(request);
    QJsonObject obj = QJsonDocument::fromJson(answer.toUtf8()).object();

    EXPECT_EQ(obj["name"].toString(), "enter_lobby");
    EXPECT_EQ(obj["data"].toObject()["session"].toString(), session("valid_user"));
}

TEST_F(OveviewTest, request_user_and_session)
{
    EXPECT_TRUE(createUser("new_user", "secret"));

    EXPECT_EQ(username("secret"), "new_user");
    EXPECT_EQ(session("new_user"), "secret");
}
