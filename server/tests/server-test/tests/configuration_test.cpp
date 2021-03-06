#include <gmock/gmock.h>

#include <utils/configuration.h>

#include <test_utils/mocked_server.h>

TEST(ConfigurationTest, DISABLED_construct_simple)
{
    Configuration conf(MockedServer::application());
}

TEST(ConfigurationTest, DISABLED_server_port)
{
    Configuration conf(MockedServer::application());
    EXPECT_EQ(conf.port(), 31415);
}
