#include <gmock/gmock.h>

#include <QJsonDocument>
#include <QSignalSpy>
#include <QUrl>
#include <QWebSocket>

#include <network/websocketserver.h>
#include <utils/exception.h>

#include <test_utils/mocked_server.h>

TEST(WebSocketServerTest, connect_invalid_route)
{
    QWebSocket client;

    QSignalSpy disconnected_spy(&client, &QWebSocket::disconnected);
    QSignalSpy message_spy(&client, &QWebSocket::textMessageReceived);

    client.open(QUrl("ws://localhost:31415/invalid"));

    EXPECT_TRUE(disconnected_spy.size() || disconnected_spy.wait());
    EXPECT_TRUE(message_spy.size() || message_spy.wait());

    EXPECT_EQ(disconnected_spy.size(), 1);
    ASSERT_EQ(message_spy.size(), 1);

    const auto string = message_spy.at(0).at(0).toString();
    const auto json = QJsonDocument::fromJson(string.toUtf8());
    EXPECT_TRUE(json["error"].isObject());
    EXPECT_EQ(json["error"]["id"].toInt(), Exception::InvalidRoute);

    EXPECT_FALSE(client.isValid());
}

TEST(WebSocketServerTest, connect_overview_route)
{
    QWebSocket client;

    QSignalSpy connected_spy(&client, &QWebSocket::connected);
    QSignalSpy message_spy(&client, &QWebSocket::textMessageReceived);

    client.open(QUrl("ws://localhost:31415/"));

    EXPECT_TRUE(connected_spy.size() || connected_spy.wait());
    EXPECT_EQ(message_spy.size(), 0);

    client.sendTextMessage("invalid message format.");

    EXPECT_TRUE(message_spy.size() || message_spy.wait());

    EXPECT_EQ(connected_spy.size(), 1);
    ASSERT_EQ(message_spy.size(), 1);

    const auto string = message_spy.at(0).at(0).toString();
    const auto json = QJsonDocument::fromJson(string.toUtf8());
    EXPECT_TRUE(json["error"].isObject());
    EXPECT_EQ(json["error"]["id"].toInt(), Exception::MalformedRequest);

    EXPECT_TRUE(client.isValid());
}

TEST(WebSocketServerTest, connect_lobby_route_no_auth)
{
    QWebSocket client;

    QSignalSpy disconnected_spy(&client, &QWebSocket::disconnected);
    QSignalSpy message_spy(&client, &QWebSocket::textMessageReceived);

    client.open(QUrl("ws://localhost:31415/lobby"));

    EXPECT_TRUE(disconnected_spy.size() || disconnected_spy.wait());
    EXPECT_TRUE(message_spy.size() || message_spy.wait());

    EXPECT_EQ(disconnected_spy.size(), 1);
    ASSERT_EQ(message_spy.size(), 1);

    const auto string = message_spy.at(0).at(0).toString();
    const auto json = QJsonDocument::fromJson(string.toUtf8());
    EXPECT_TRUE(json["error"].isObject());
    EXPECT_NE(json["error"]["id"].toInt(), Exception::InvalidRoute);

    EXPECT_FALSE(client.isValid());
}

TEST(WebSocketServerTest, connect_game_route_no_auth)
{
    QWebSocket client;

    QSignalSpy disconnected_spy(&client, &QWebSocket::disconnected);
    QSignalSpy message_spy(&client, &QWebSocket::textMessageReceived);

    client.open(QUrl("ws://localhost:31415/game"));

    EXPECT_TRUE(disconnected_spy.size() || disconnected_spy.wait());
    EXPECT_TRUE(message_spy.size() || message_spy.wait());

    EXPECT_EQ(disconnected_spy.size(), 1);
    ASSERT_EQ(message_spy.size(), 1);

    const auto string = message_spy.at(0).at(0).toString();
    const auto json = QJsonDocument::fromJson(string.toUtf8());
    EXPECT_TRUE(json["error"].isObject());
    EXPECT_NE(json["error"]["id"].toInt(), Exception::InvalidRoute);

    EXPECT_FALSE(client.isValid());
}
