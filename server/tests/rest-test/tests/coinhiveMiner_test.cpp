
#include <gmock/gmock.h>

#include <rest_apis/coinhive.h>

#include <QSignalSpy>

#include <test-utils/MockCoinhiveServer.h>

TEST(CoinhiveMinerTest, fullRun)
{
    MockCoinhiveServer server;

    rest_apis::coinhive::MiningSupervisor tested(1, 1024, "http://localhost:80");

    QSignalSpy miningSpy(&tested, &rest_apis::coinhive::MiningSupervisor::userMined);

    ASSERT_TRUE(miningSpy.wait(1500)); // wait for first signal, timeout 1/2 sec + 1 sec supervisor interval

    while (miningSpy.wait(100)) {} // wait for remaining signals

    ASSERT_EQ(miningSpy.size(), 2);

    const auto firstName    = miningSpy[0][0];
    const auto firstBlocks  = miningSpy[0][1];
    const auto secondName   = miningSpy[1][0];
    const auto secondBlocks = miningSpy[1][1];

    EXPECT_EQ(firstName.type(), QVariant::String);
    EXPECT_EQ(firstBlocks.type(), QVariant::Int);
    EXPECT_EQ(secondName.type(), QVariant::String);
    EXPECT_EQ(secondBlocks.type(), QVariant::Int);

    EXPECT_EQ(firstName.toString(), "Rich Guy");
    EXPECT_EQ(firstBlocks.toInt(), 4);
    EXPECT_EQ(secondName.toString(), "Poor Guy");
    EXPECT_EQ(secondBlocks.toInt(), 1);
    // "Broke Bloke" has not enough to withdraw, so he doesn't create a withdraw request or a mining signal
}
