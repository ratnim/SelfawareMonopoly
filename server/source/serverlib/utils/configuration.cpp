#include "configuration.h"

Configuration::Configuration(const QCoreApplication& application)
{
    auto args = QCoreApplication::arguments();
    m_parser.addOption(portOption());
    m_parser.process(application);
}

uint16_t Configuration::port() const
{
    return m_parser.value(portOption()).toInt();
}

QCommandLineOption Configuration::portOption()
{
    return { "port", "The port used to listen for websocket connections.", "", "31415" };
}
