#pragma once

#include <route.h>

class Game : public Route
{
public:
    void connectClient(QWebSocket* socket, const Request& request) override;
};
