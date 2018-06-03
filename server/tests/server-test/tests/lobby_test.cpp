#include <gmock/gmock.h>

#include <QJsonDocument>

#include <routes/lobbyroute.h>

#include <test_utils/mocked_database.h>


class LobbyTest : public ::testing::Test, MockedDatabase, public LobbyRoute
{
public:
    LobbyTest()
        : LobbyRoute()
    {
    }
};

TEST_F(LobbyTest, unsupported_action)
{
    QJsonObject request({ { "request", "something" } });

    auto answer = handle(request, "registered_player");

    EXPECT_EQ(answer["error"].toObject()["id"].toInt(), Route::UnsupportedAction);
}

TEST_F(LobbyTest, create_GameRoute_invalid_player)
{
    QJsonObject request({ { "request", "create_GameRoute" } });

    auto answer = handle(request, "unregistered_player");

    EXPECT_EQ(answer["error"].toObject()["id"].toInt(), Route::InvalidRequest);
}

TEST_F(LobbyTest, create_GameRoute_valid)
{
    QJsonObject request({ { "request", "create_GameRoute" } });

    auto answer = handle(request, "registered_player");

    EXPECT_EQ(answer["name"].toString(), "create_GameRoute");
    EXPECT_NE(answer["name"].toObject()["game_id"].toInt(-1), -1);
}

TEST_F(LobbyTest, join_GameRoute_invalid_id)
{
    QJsonObject request({ { "request", "join_GameRoute" }, { "data", QJsonObject{ { "game_id", "1" } } } });

    auto answer = handle(request, "registered_player");

    EXPECT_EQ(answer["error"].toObject()["id"].toInt(), Route::InvalidRequest);
}

TEST_F(LobbyTest, join_GameRoute_already_started)
{
    QJsonObject request({ { "request", "join_GameRoute" }, { "data", QJsonObject{ { "game_id", "1" } } } });

    auto answer = handle(request, "registered_player");

    EXPECT_EQ(answer["error"].toObject()["id"].toInt(), Route::InvalidRequest);
}

TEST_F(LobbyTest, join_GameRoute_invalid_player)
{
    QJsonObject request({ { "request", "join_GameRoute" }, { "data", QJsonObject{ { "game_id", "1" } } } });

    auto answer = handle(request, "unregistered_player");

    EXPECT_EQ(answer["error"].toObject()["id"].toInt(), Route::InvalidRequest);
}

TEST_F(LobbyTest, join_GameRoute_valid)
{
    QJsonObject request({ { "request", "join_GameRoute" }, { "data", QJsonObject{ { "game_id", "1" } } } });

    auto answer = handle(request, "unregistered_player");

    EXPECT_EQ(answer["name"].toString(), "join_GameRoute");
    EXPECT_NE(answer["name"].toObject()["game_id"].toInt(-1), -1);
}
