#include <gmock/gmock.h>

#include <QJsonDocument>

#include <lobby.h>
#include <mocked_database.h>


class LobbyTest : public ::testing::Test, MockedDatabase, public Lobby
{
public:
    LobbyTest()
        : Lobby(accounts)
    {
    }
};

TEST_F(LobbyTest, unsupported_action)
{
    QJsonObject request({ { "request", "something" } });

    auto answer = handle(request, "registered_player");

    EXPECT_EQ(answer["error"].toObject()["id"].toInt(), Route::UnsupportedAction);
}

TEST_F(LobbyTest, create_game_invalid_player)
{
    QJsonObject request({ { "request", "create_game" } });

    auto answer = handle(request, "unregistered_player");

    EXPECT_EQ(answer["error"].toObject()["id"].toInt(), Route::InvalidRequest);
}

TEST_F(LobbyTest, create_game_valid)
{
    QJsonObject request({ { "request", "create_game" } });

    auto answer = handle(request, "registered_player");

    EXPECT_EQ(answer["name"].toString(), "create_game");
    EXPECT_NE(answer["name"].toObject()["game_id"].toInt(-1), -1);
}

TEST_F(LobbyTest, join_game_invalid_id)
{
    QJsonObject request({ { "request", "join_game" }, { "data", QJsonObject{ { "game_id", "1" } } } });

    auto answer = handle(request, "registered_player");

    EXPECT_EQ(answer["error"].toObject()["id"].toInt(), Route::InvalidRequest);
}

TEST_F(LobbyTest, join_game_already_started)
{
    QJsonObject request({ { "request", "join_game" }, { "data", QJsonObject{ { "game_id", "1" } } } });

    auto answer = handle(request, "registered_player");

    EXPECT_EQ(answer["error"].toObject()["id"].toInt(), Route::InvalidRequest);
}

TEST_F(LobbyTest, join_game_invalid_player)
{
    QJsonObject request({ { "request", "join_game" }, { "data", QJsonObject{ { "game_id", "1" } } } });

    auto answer = handle(request, "unregistered_player");

    EXPECT_EQ(answer["error"].toObject()["id"].toInt(), Route::InvalidRequest);
}

TEST_F(LobbyTest, join_game_valid)
{
    QJsonObject request({ { "request", "join_game" }, { "data", QJsonObject{ { "game_id", "1" } } } });

    auto answer = handle(request, "unregistered_player");

    EXPECT_EQ(answer["name"].toString(), "join_game");
    EXPECT_NE(answer["name"].toObject()["game_id"].toInt(-1), -1);
}
