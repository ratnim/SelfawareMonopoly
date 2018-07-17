
#include <gmock/gmock.h>

#include <QSignalSpy>

#include <test-utils/MockBasicRestServer.h>

#include <rest_apis/restAPIsBase.h>

TEST(RestBaseTest, get)
{
    MockBasicRestServer server;

    auto response = rest_apis::sendGET(QUrl("http://localhost"));

    QSignalSpy finishSpy(response, &QNetworkReply::finished);

    EXPECT_TRUE(finishSpy.size() || finishSpy.wait());

    ASSERT_EQ(finishSpy.size(), 1);

    const auto content = response->readAll();

    ASSERT_EQ(content, "GET");
}

TEST(RestBaseTest, post)
{
    MockBasicRestServer server;

    auto response = rest_apis::sendPOST(QUrl("http://localhost"), QByteArray());

    QSignalSpy finishSpy(response, &QNetworkReply::finished);

    EXPECT_TRUE(finishSpy.size() || finishSpy.wait());

    ASSERT_EQ(finishSpy.size(), 1);

    const auto content = response->readAll();

    ASSERT_EQ(content, "POST");
}

TEST(RestBaseTest, put)
{
    MockBasicRestServer server;

    auto response = rest_apis::sendPUT(QUrl("http://localhost"), QByteArray());

    QSignalSpy finishSpy(response, &QNetworkReply::finished);

    EXPECT_TRUE(finishSpy.size() || finishSpy.wait());

    ASSERT_EQ(finishSpy.size(), 1);

    const auto content = response->readAll();

    ASSERT_EQ(content, "PUT");
}

TEST(RestBaseTest, delete)
{
    MockBasicRestServer server;

    auto response = rest_apis::sendDELETE(QUrl("http://localhost"));

    QSignalSpy finishSpy(response, &QNetworkReply::finished);

    EXPECT_TRUE(finishSpy.size() || finishSpy.wait());

    ASSERT_EQ(finishSpy.size(), 1);

    const auto content = response->readAll();

    ASSERT_EQ(content, "DELETE");
}
