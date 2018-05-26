#include "configuration.h"

Configuration::Configuration(const QCoreApplication& application)
{
    m_parser.addOption(rootDirectoryOption());
    m_parser.addOption(encryptConnectionOption());
    m_parser.process(application);
}

QString Configuration::rootDirectory() const
{
    return m_parser.value(rootDirectoryOption());
}

bool Configuration::encryptConnection() const
{
    return m_parser.isSet(encryptConnectionOption());
}

QCommandLineOption Configuration::rootDirectoryOption()
{
    return { "root-directory", "The root directory used to serve static files used by the client.", "", "../../../../client" };
}

QCommandLineOption Configuration::encryptConnectionOption()
{
    return { "encrypt-conection", "Use encryption for all client-server communication." };
}
