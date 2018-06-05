#pragma once

#include <QCoreApplication>
#include <QCommandLineParser>

class Configuration
{
public:
    Configuration(const QCoreApplication& application);

    uint16_t port() const;

protected:
    static QCommandLineOption portOption();
    
    QCommandLineParser m_parser;
};
