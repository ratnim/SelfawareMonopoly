#include <gmock/gmock.h>

#include <test_utils/mocked_server.h>

int main(int argc, char* argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    //MockedServer::constructServer(argc, argv);
    return RUN_ALL_TESTS();
}
