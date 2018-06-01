#pragma once

#include <models/accountmodel.h>
#include <routes/playercommunication.h>

class Lobby : public PlayerCommunication
{
public:
    Lobby(QWebSocket* socket, const Request& request);
};
