#include <gmock/gmock.h>

#include <network/websocketserver.h>

TEST(RequestTest, empthy_string)
{
    auto request = Request::fromUrl("");

    EXPECT_TRUE(request.route.isEmpty());
    EXPECT_TRUE(request.session.isEmpty());
    EXPECT_TRUE(request.GameRouteId.isEmpty());
}

TEST(RequestTest, root_path)
{
    auto request = Request::fromUrl("ws://localhost/");

    EXPECT_TRUE(request.route.isEmpty());
    EXPECT_TRUE(request.session.isEmpty());
    EXPECT_TRUE(request.GameRouteId.isEmpty());
}

TEST(RequestTest, non_root_path)
{
    auto request = Request::fromUrl("ws://localhost/LobbyRoute");

    EXPECT_EQ(request.route, "LobbyRoute");
    EXPECT_TRUE(request.session.isEmpty());
    EXPECT_TRUE(request.GameRouteId.isEmpty());
}

TEST(RequestTest, non_root_path_with_unused_parameters)
{
    auto request = Request::fromUrl("ws://localhost/LobbyRoute?yo=1&b=4");

    EXPECT_EQ(request.route, "LobbyRoute");
    EXPECT_TRUE(request.session.isEmpty());
    EXPECT_TRUE(request.GameRouteId.isEmpty());
}

TEST(RequestTest, non_root_path_with_unused_and_used_parameters)
{
    auto request = Request::fromUrl("ws://localhost/LobbyRoute?yo=1&b=4&session=123&game_id=321");

    EXPECT_EQ(request.route, "LobbyRoute");
    EXPECT_EQ(request.session.toStdString(), "123");
    EXPECT_EQ(request.GameRouteId.toStdString(), "321");
}
