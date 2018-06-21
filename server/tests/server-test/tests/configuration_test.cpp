#include <gmock/gmock.h>

#include <utils/configuration.h>

#include <test_utils/mocked_server.h>

TEST(ConfigurationTest, construct_simple)
{
    Configuration conf(MockedServer::application());
}

TEST(ConfigurationTest, server_port)
{
    Configuration conf(MockedServer::application());
    EXPECT_EQ(conf.port(), 31415);
}
