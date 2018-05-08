#include <iostream>

#include <QApplication>
#include <QDebug>

#include <server.h>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    Server server;
    server.run();

    return 0;
}
