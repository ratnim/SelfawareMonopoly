#include <gmock/gmock.h>

#include <QJsonDocument>

#include <mocked_server.h>
#include <overview.h>
#include <websocketserver.h>

struct State
{
    OverviewState overview;
};

class OverviewTest : public ::testing::Test, public State, public Overview
{
public:
    OverviewTest()
        : Overview(overview)
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
    EXPECT_TRUE(m_state.createUser("test_user", session()));

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
    EXPECT_EQ(answer["data"].toObject()["session"].toString(), m_state.session("valid_user"));
}

TEST_F(OverviewTest, request_user_and_session)
{
    EXPECT_TRUE(m_state.createUser("new_user", "secret"));

    EXPECT_EQ(m_state.username("secret"), "new_user");
    EXPECT_EQ(m_state.session("new_user"), "secret");
}
