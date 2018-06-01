#pragma once

#include <routes/playercommunication.h>

class Game : public PlayerCommunication
{
public:
    Game(QWebSocket* socket, const Request& request);
};
