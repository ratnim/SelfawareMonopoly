#include <gmock/gmock.h>

#include <models/boardmodel.h>

class BoardModelTest : public ::testing::Test
{
public:
};

TEST_F(BoardModelTest, get_board_model_instance)
{
    auto& instance = BoardModel::instance();
}