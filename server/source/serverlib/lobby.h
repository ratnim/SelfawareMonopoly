#pragma once

#include <route.h>

class Lobby : public Route
{
public:
    void mount(QWebSocket* socket) override;
};
