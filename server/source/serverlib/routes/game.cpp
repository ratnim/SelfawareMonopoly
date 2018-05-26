#include "game.h"

void Game::connectClient(QWebSocket* socket, const Request& request)
{
    connect(socket, &QWebSocket::textMessageReceived, [this, socket](const QString& message) {
        // TODO
    });

    connect(socket, &QWebSocket::readChannelFinished, this, [this, socket] {
        disconnectClient(socket);
    });
}
