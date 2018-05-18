#pragma once

#include <QApplication>
#include <QCommandLineParser>

class Configuration
{
public:
    Configuration(const QApplication& application);

    QString rootDirectory() const;

protected:
    static QCommandLineOption rootDirectoryOption();
    
    QCommandLineParser m_parser;
};
