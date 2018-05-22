#include <gmock/gmock.h>

#include <mocked_server.h>

int main(int argc, char* argv[])
{
    MockedServer::constructServer(argc, argv);

    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
