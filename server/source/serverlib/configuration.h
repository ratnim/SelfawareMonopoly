#pragma once

#include <QApplication>
#include <QCommandLineParser>

class Configuration
{
public:
    Configuration(const QCoreApplication& application);

    QString rootDirectory() const;
    bool encryptConnection() const;

protected:
    static QCommandLineOption rootDirectoryOption();
    static QCommandLineOption encryptConnectionOption();
    
    QCommandLineParser m_parser;
};
