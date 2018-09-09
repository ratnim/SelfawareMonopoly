#include <gmock/gmock.h>

#include <game/board/board.h>
#include <game/board/station.h>

#include <test_utils/helpers.h>

TEST(StationTest, get_description)
{
    Station station("Test", 5, 200, 100);

    auto description = station.description();

    EXPECT_EQ("Test", description["name"].toString().toStdString());
    EXPECT_EQ("station", description["type"].toString().toStdString());
    EXPECT_EQ(5, description["group"].toInt());
    EXPECT_EQ(200, description["price"].toInt());
    EXPECT_EQ(100, description["base_rent"].toInt());
}

// State transfers are commmon to all OwnableFields

TEST(StationTest, rent_calculation)
{
    Board board(std::move(fieldsStations()));

    auto stationA = dynamic_cast<Station*>(board[1]); // Group 0
    auto stationB = dynamic_cast<Station*>(board[2]); // Group 0
    auto stationC = dynamic_cast<Station*>(board[3]); // Group 0
    auto stationD = dynamic_cast<Station*>(board[4]); // Group 1

    // All stations are owned by "", so maximum owner bonus applies
    EXPECT_EQ(400, stationA->rent(board)); // 100 * 2**2
    EXPECT_EQ(200, stationD->rent(board)); // 200

    // Split ownership of group 0
    stationC->changeOwner("someone");

    EXPECT_EQ(200, stationA->rent(board)); // 100 * 2
    EXPECT_EQ(100, stationC->rent(board)); // 100
    EXPECT_EQ(200, stationD->rent(board)); // 200
}
