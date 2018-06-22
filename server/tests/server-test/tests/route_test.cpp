#include <gmock/gmock.h>

#include <QJsonDocument>
#include <QJsonObject>
#include <QSignalSpy>

#include <routes/route.h>
#include <utils/exception.h>

namespace
{
QWebSocket dummy;
}

class SubRouteTest : public ::testing::Test, public Route
{
public:
    SubRouteTest()
        : Route(&dummy)
    {
        m_actions["test"] = [this](const QJsonValue& input) {
            data = input;
            send("ok");
        };
    }

    QJsonValue data;
};

TEST(RouteTest, parent_ownership)
{
    QWebSocket socket;
    auto route = new Route(&socket);

    EXPECT_TRUE(route->parent() == &socket);
}

TEST_F(SubRouteTest, non_json_message)
{
    QSignalSpy socket_spy(this, &Watcher::send);

    incommingMessage(";not json");

    ASSERT_TRUE(socket_spy.size() || socket_spy.wait());
    EXPECT_TRUE(data.isNull());

    auto json = toJson(socket_spy.at(0).at(0).toString());
    EXPECT_EQ(json["error"].toObject()["id"].toInt(), error::MalformedRequest);
}

TEST_F(SubRouteTest, unknown_action)
{
    QSignalSpy socket_spy(this, &Watcher::send);

    QJsonObject in({ { "request", "someaction" } });

    incommingMessage(QJsonDocument(in).toJson());

    ASSERT_TRUE(socket_spy.size() || socket_spy.wait());
    EXPECT_TRUE(data.isNull());

    auto json = toJson(socket_spy.at(0).at(0).toString());
    EXPECT_EQ(json["error"].toObject()["id"].toInt(), error::UnsupportedAction);
}

TEST_F(SubRouteTest, valid_message)
{
    QSignalSpy socket_spy(this, &Watcher::send);

    QJsonObject in({ { "request", "test" } });

    incommingMessage(QJsonDocument(in).toJson());

    ASSERT_TRUE(socket_spy.size() || socket_spy.wait());
    EXPECT_FALSE(data.isNull());

    auto answer = socket_spy.at(0).at(0).toString();
    EXPECT_EQ(answer, "ok");
}
