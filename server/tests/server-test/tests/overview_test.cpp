#include <gmock/gmock.h>

#include <QJsonDocument>

#include <routes/overviewroute.h>

#include <test_utils/mocked_database.h>

class OverviewRouteTest : public ::testing::Test, MockedDatabase, public OverviewRoute
{
public:
    OverviewRouteTest()
        : OverviewRoute(accounts)
    {
    }
};

TEST_F(OverviewRouteTest, unsupported_action)
{
    QJsonObject request({ { "request", "something" } });

    auto answer = handle(request);

    EXPECT_EQ(answer["error"].toObject()["id"].toInt(), Route::UnsupportedAction);
}

TEST_F(OverviewRouteTest, invalid_request_no_data)
{
    QJsonObject request({ { "request", "enter_LobbyRoute" } });

    auto answer = handle(request);

    EXPECT_EQ(answer["error"].toObject()["id"].toInt(), Route::MalformedRequest);
}

TEST_F(OverviewRouteTest, invalid_request_no_player_name)
{
    QJsonObject request({ { "request", "enter_LobbyRoute" } });
    request["data"] = QJsonObject();

    auto answer = handle(request);

    EXPECT_EQ(answer["error"].toObject()["id"].toInt(), Route::MalformedRequest);
}

TEST_F(OverviewRouteTest, user_error_player_name_taken)
{
    EXPECT_NE(m_state.createUser("test_user"), QString());

    QJsonObject request({ { "request", "enter_LobbyRoute" } });
    QJsonObject data({ { "player_name", "test_user" } });
    request["data"] = data;

    auto answer = handle(request);

    EXPECT_EQ(answer["error"].toObject()["id"].toInt(), Route::InvalidRequest);
}

TEST_F(OverviewRouteTest, correct_request)
{
    QJsonObject request({ { "request", "enter_LobbyRoute" } });
    QJsonObject data({ { "player_name", "valid_user" } });
    request["data"] = data;

    auto answer = handle(request);

    EXPECT_EQ(answer["name"].toString(), "enter_LobbyRoute");

    const auto session = answer["data"].toObject()["session"].toString();
    EXPECT_NE(session, QString());
    EXPECT_EQ(m_state.username(session), "valid_user");
}

TEST_F(OverviewRouteTest, request_user_and_session)
{
    EXPECT_EQ(m_state.username(m_state.createUser("new_user")), "new_user");

    const auto session = m_state.createSession("another_user");
    EXPECT_NE(session, QString());
    EXPECT_EQ(m_state.username(session), "another_user");
}
