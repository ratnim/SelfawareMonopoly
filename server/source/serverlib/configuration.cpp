#include "configuration.h"

Configuration::Configuration(const QApplication& application)
{
    m_parser.addOption(rootDirectoryOption());
    m_parser.process(application);
}

QString Configuration::rootDirectory() const
{
    return m_parser.value(rootDirectoryOption());
}

QCommandLineOption Configuration::rootDirectoryOption()
{
    return {"root-directory", "The root directory used to serve static files used by the client", "", "../../../../client"};
}
