#include "mocked_server.h"

#include <thread>

#include <QWebSocket>

namespace
{
QCoreApplication* s_app;
}

QCoreApplication& MockedServer::application()
{
    return *s_app;
}

MockedServer::MockedServer(int argc, char** argv)
    : m_app(argc, argv)
    , m_srv(QHostAddress::LocalHost)
    , m_prog()
{
    s_app = &m_app;
}
