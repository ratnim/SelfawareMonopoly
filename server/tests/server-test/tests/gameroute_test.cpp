#include <gmock/gmock.h>

#include <QJsonDocument>
#include <QJsonObject>
#include <QSignalSpy>

#include <routes/gameroute.h>

#include <models/accountmodel.h>
#include <models/gamemodel.h>
#include <models/boardmodel.h>
#include <network/request.h>

namespace
{
QWebSocket dummy;
}

TEST(GameRouteTest, request_board)
{
    auto session = AccountModel::instance().createSession("request_board_tester");
    auto gameId = GameModel::instance().createGame("request_board_game");
	Request request("game", session, gameId);

    QWebSocket socket;
    auto route = new GameRoute(&socket, request);

    QSignalSpy socket_spy(route, &Watcher::send);
    
	QJsonObject in({ { "request", "game_board" } });

    route->incommingMessage(QJsonDocument(in).toJson());
	
	ASSERT_TRUE(socket_spy.size() || socket_spy.wait());

	auto json = route->toJson(socket_spy.at(0).at(0).toString());

	EXPECT_NE(json["data"].toObject().end(), json["data"].toObject().find("fields"));
}

TEST(GameRouteTest, request_non_empty_board)
{
	BoardModel::setBoardDir("./assets/boards");
    auto session = AccountModel::instance().createSession("request_non_empty_board_tester");
    auto gameId = GameModel::instance().createGame("request_non_empty_board_game", "berlin.json");
    Request request("game", session, gameId);

    QWebSocket socket;
    auto route = new GameRoute(&socket, request);

    QSignalSpy socket_spy(route, &Watcher::send);

    QJsonObject in({ { "request", "game_board" } });

    route->incommingMessage(QJsonDocument(in).toJson());

    ASSERT_TRUE(socket_spy.size() || socket_spy.wait());

	auto msg = socket_spy.at(0).at(0).toString().toStdString();
    auto json = route->toJson(socket_spy.at(0).at(0).toString());
    auto fields = json["data"].toObject()["fields"].toArray();

    EXPECT_EQ(40, fields.size());
}
