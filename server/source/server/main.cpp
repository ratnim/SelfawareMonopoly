#include <iostream>

#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>

#include <configuration.h>
#include <fileserver.h>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Configuration conv(app);

    FileServer server(conv.rootDirectory());

    return app.exec();
}
