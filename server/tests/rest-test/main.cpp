
#include <gmock/gmock.h>

#include <QApplication>

#include <rest_apis/coinhive.h>

int main(int argc, char** argv)
{
    ::testing::InitGoogleMock(&argc, argv);

    QApplication app(argc, argv);

    return RUN_ALL_TESTS();
}