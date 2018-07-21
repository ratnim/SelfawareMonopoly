#pragma once

#include <QCoreApplication>

#include <network/websocketserver.h>
#include <utils/program.h>

class MockedServer
{
public:
    MockedServer(int arg, char** argv);

    static QCoreApplication& application();

protected:
    QCoreApplication m_app;
    WebSocketServer m_srv;
    Program m_prog;
};
