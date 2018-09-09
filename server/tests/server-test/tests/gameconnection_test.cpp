#include <gmock/gmock.h>

#include <QJsonDocument>
#include <QJsonObject>
#include <QSignalSpy>

#include <connections/gameconnection.h>

#include <models/accountmodel.h>
#include <models/gamemodel.h>
#include <models/boardmodel.h>
#include <network/connectionrequest.h>

namespace
{
QWebSocket dummy;
}

TEST(GameConnectionTest, request_board)
{
    QWebSocket socket;
    auto session = AccountModel::instance().createSession("request_board_tester");
    auto gameId = GameModel::instance().createGame("request_board_game");
    auto connection = new GameConnection(&socket, { "game", session, gameId });

    QSignalSpy socket_spy(connection, &Watcher::broadcast);

    connection->incommingMessage(QJsonDocument(QJsonObject{ { "request", "game_board" } }).toJson());
	
	ASSERT_TRUE(socket_spy.size() || socket_spy.wait());

	auto json = Connection::toJson(socket_spy.at(0).at(0).toString());

	EXPECT_NE(json["data"].toObject().end(), json["data"].toObject().find("fields"));
}

TEST(GameConnectionTest, request_non_empty_board)
{
	BoardModel::setBoardDir("./assets/boards");
    QWebSocket socket;
    auto session = AccountModel::instance().createSession("request_non_empty_board_tester");
    auto gameId = GameModel::instance().createGame("request_non_empty_board_game", "berlin_en.json");
    auto connection = new GameConnection(&socket, { "game", session, gameId });

    QSignalSpy socket_spy(connection, &Watcher::broadcast);

    connection->incommingMessage(QJsonDocument(QJsonObject{{ "request", "game_board" }}).toJson());

    ASSERT_TRUE(socket_spy.size() || socket_spy.wait());

	auto json = Connection::toJson(socket_spy.at(0).at(0).toString());
    auto fields = json["data"].toObject()["fields"].toArray();

    EXPECT_EQ(40, fields.size());
}

TEST(GameConnectionTest, possible_requests)
{
    QWebSocket socket_1;
    QWebSocket socket_2;
    QString player_1{"possible_requests_player_1"};
    QString player_2{"possible_requests_player_2"};
    auto session_1 = AccountModel::instance().createSession(player_1);
    auto session_2 = AccountModel::instance().createSession(player_2);
    auto gameId = GameModel::instance().createGame("possible_requests");
    auto connection_1 = new GameConnection(&socket_1, {"game", session_1, gameId});
    auto connection_2 = new GameConnection(&socket_2, {"game", session_2, gameId});

    QSignalSpy socket_spy_1(connection_1, &Watcher::broadcast);
    QSignalSpy socket_spy_2(connection_2, &Watcher::broadcast);

	auto& game = GameModel::instance().open(gameId).game;

	emit game.onPossibleRequests("not_there", {});

    ASSERT_FALSE(socket_spy_1.size() || socket_spy_1.wait(500));
    ASSERT_FALSE(socket_spy_2.size() || socket_spy_2.wait(500));

	emit game.onPossibleRequests(player_1, {});

	ASSERT_TRUE(socket_spy_1.size() || socket_spy_1.wait(500));
    ASSERT_FALSE(socket_spy_2.size() || socket_spy_2.wait(500));

	emit game.onPossibleRequests(player_2, {});

    ASSERT_EQ(1, socket_spy_1.size());
    ASSERT_TRUE(socket_spy_2.size() || socket_spy_2.wait(500));

    auto message = socket_spy_1.at(0).at(0).toString();
    auto json = Connection::toJson(message);

	EXPECT_NE(json.end(), json.find("data"));
	EXPECT_NE(json["data"].toObject().end(), json["data"].toObject().find("requests"));
}
