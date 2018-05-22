#include "lobby.h"

void Lobby::mount(QWebSocket* socket)
{
    connect(socket, &QWebSocket::textMessageReceived, [this, socket](const QString& message) {
        // TODO
    });

    connect(socket, &QWebSocket::readChannelFinished, this, [this, socket] {
        unmount(socket);
    });
}
