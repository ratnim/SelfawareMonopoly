#include <gmock/gmock.h>

#include <QJsonDocument>
#include <QJsonObject>
#include <QSignalSpy>

#include <connections/connection.h>
#include <utils/exception.h>

namespace
{
QWebSocket dummy;
}

class SubConnectionTest : public ::testing::Test, public Connection
{
public:
    SubConnectionTest()
        : Connection(&dummy)
    {
        m_requests["test"] = [this](const QJsonValue& input) {
            data = input;
            broadcast("ok");
        };
    }

    QJsonValue data;
};

TEST(RouteTest, parent_ownership)
{
    QWebSocket socket;
    auto route = new Connection(&socket);

    EXPECT_TRUE(route->parent() == &socket);
}

TEST_F(SubConnectionTest, non_json_message)
{
    QSignalSpy socket_spy(this, &Watcher::broadcast);

    incommingMessage(";not json");

    ASSERT_TRUE(socket_spy.size() || socket_spy.wait());
    EXPECT_TRUE(data.isNull());

    auto json = toJson(socket_spy.at(0).at(0).toString());
    EXPECT_EQ(json["data"].toObject()["id"].toInt(), Error::MalformedRequest);
}

TEST_F(SubConnectionTest, unknown_action)
{
    QSignalSpy socket_spy(this, &Watcher::broadcast);

    QJsonObject in({ { "request", "someaction" } });

    incommingMessage(QJsonDocument(in).toJson());

    ASSERT_TRUE(socket_spy.size() || socket_spy.wait());
    EXPECT_TRUE(data.isNull());

    auto json = toJson(socket_spy.at(0).at(0).toString());
    EXPECT_EQ(json["data"].toObject()["id"].toInt(), Error::UnsupportedAction);
}

TEST_F(SubConnectionTest, valid_message)
{
    QSignalSpy socket_spy(this, &Watcher::broadcast);

    QJsonObject in({ { "request", "test" } });

    incommingMessage(QJsonDocument(in).toJson());

    ASSERT_TRUE(socket_spy.size() || socket_spy.wait());
    EXPECT_FALSE(data.isNull());

    auto answer = socket_spy.at(0).at(0).toString();
    EXPECT_EQ(answer, "ok");
}
