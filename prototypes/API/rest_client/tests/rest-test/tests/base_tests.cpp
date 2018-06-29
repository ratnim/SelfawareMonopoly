
#include <gmock/gmock.h>

#include <restAPIsBase.h>

TEST(BaseTest, get)
{
    auto reply = rest_apis::sendGET(QUrl("http://localhost:80/"));

    EXPECT_EQ(reply.length(), 3);
    EXPECT_EQ(reply.toStdString(), "GET");
}

TEST(BaseTest, delete)
{
    auto reply = rest_apis::sendDELETE(QUrl("http://localhost:80/"));

    EXPECT_EQ(reply.length(), 6);
    EXPECT_EQ(reply.toStdString(), "DELETE");
}

TEST(BaseTest, post)
{
    auto reply = rest_apis::sendPOST(QUrl("http://localhost:80/"), QByteArray());

    EXPECT_EQ(reply.length(), 4);
    EXPECT_EQ(reply.toStdString(), "POST");
}

TEST(BaseTest, put)
{
    auto reply = rest_apis::sendPUT(QUrl("http://localhost:80/"), QByteArray());

    EXPECT_EQ(reply.length(), 3);
    EXPECT_EQ(reply.toStdString(), "PUT");
}
