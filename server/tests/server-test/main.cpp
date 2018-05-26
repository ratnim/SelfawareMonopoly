#include <gmock/gmock.h>

#include <test_utils/mocked_server.h>

int main(int argc, char* argv[])
{
    MockedServer::constructServer(argc, argv);

    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
