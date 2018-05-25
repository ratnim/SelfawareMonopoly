#include <gmock/gmock.h>

#include <QJsonDocument>

#include <mocked_database.h>

#include <overview.h>

class OverviewTest : public ::testing::Test, MockedDatabase, public Overview
{
public:
    OverviewTest()
        : Overview(accounts)
    {
    }
};

TEST_F(OverviewTest, unsupported_action)
{
    QJsonObject request({ { "request", "something" } });

    auto answer = handle(request);

    EXPECT_EQ(answer["error"].toObject()["id"].toInt(), Route::UnsupportedAction);
}

TEST_F(OverviewTest, invalid_request_no_data)
{
    QJsonObject request({ { "request", "enter_lobby" } });

    auto answer = handle(request);

    EXPECT_EQ(answer["error"].toObject()["id"].toInt(), Route::InvalidRequest);
}

TEST_F(OverviewTest, invalid_request_no_player_name)
{
    QJsonObject request({ { "request", "enter_lobby" } });
    request["data"] = QJsonObject();

    auto answer = handle(request);

    EXPECT_EQ(answer["error"].toObject()["id"].toInt(), Route::InvalidRequest);
}

TEST_F(OverviewTest, user_error_player_name_taken)
{
    EXPECT_NE(m_state.createUser("test_user"), QString());

    QJsonObject request({ { "request", "enter_lobby" } });
    QJsonObject data({ { "player_name", "test_user" } });
    request["data"] = data;

    auto answer = handle(request);

    EXPECT_EQ(answer["error"].toObject()["id"].toInt(), Route::UserError);
}

TEST_F(OverviewTest, correct_request)
{
    QJsonObject request({ { "request", "enter_lobby" } });
    QJsonObject data({ { "player_name", "valid_user" } });
    request["data"] = data;

    auto answer = handle(request);

    EXPECT_EQ(answer["name"].toString(), "enter_lobby");

    const auto session = answer["data"].toObject()["session"].toString();
    EXPECT_NE(session, QString());
    EXPECT_EQ(m_state.username(session), "valid_user");
}

TEST_F(OverviewTest, request_user_and_session)
{
    EXPECT_EQ(m_state.username(m_state.createUser("new_user")), "new_user");

    const auto session = m_state.createSession("another_user");
    EXPECT_NE(session, QString());
    EXPECT_EQ(m_state.username(session), "another_user");
}
