#include <gmock/gmock.h>

#include <QSignalSpy>
#include <QUrl>
#include <QWebSocket>

#include <network/websocketserver.h>

#include <test_utils/mocked_server.h>

TEST(WebSocketServerTest, construct_simple)
{
    /*
    WebSocketServer server;

    QString text;

    QWebSocket client;
    QObject::connect(&client, &QWebSocket::textMessageReceived, [&text](const QString msg) { text = msg; });
    //QSignalSpy client_spy(&client, &QWebSocket::textMessageReceived);
    client.open(QUrl("ws://localhost:31415/invalid_route"));


    int x = 1000;
    while (--x)
    {
        MockedServer::application().processEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }

    EXPECT_EQ(text.toStdString(), "yolo");
    */
}
