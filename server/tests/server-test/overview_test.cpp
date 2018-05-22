#include <gmock/gmock.h>

#include <QJsonDocument>

#include <mocked_server.h>
#include <overview.h>

class OveviewTest : public ::testing::Test, public Overview
{
public:
};

TEST_F(OveviewTest, invalid_action)
{
    auto& server = MockedServer::server();
    auto connection = server.createConnection();

    QJsonObject request;
    request["request"] = "something";
    auto answer = handle(request);
    QJsonObject obj = QJsonDocument::fromJson(answer.toLatin1()).object();

    EXPECT_EQ(obj["error"].toObject()["id"].toInt(), Route::UnsupportedAction);
}
