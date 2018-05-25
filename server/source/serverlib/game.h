#pragma once

#include <route.h>

class Game : public Route
{
public:
    void mount(QWebSocket* socket, const Request& request) override;
};
