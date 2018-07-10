
#include <gmock/gmock.h>

#include <QApplication>

#include <test-utils/MockRestServer.h>

int main(int argc, char** argv)
{
    ::testing::InitGoogleMock(&argc, argv);

    QApplication app(argc, argv);
    MockRestServer server;

    return RUN_ALL_TESTS();
}