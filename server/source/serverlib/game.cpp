#include "game.h"

void Game::mount(QWebSocket* socket, const Request& request)
{
    connect(socket, &QWebSocket::textMessageReceived, [this, socket](const QString& message) {
        // TODO
    });

    connect(socket, &QWebSocket::readChannelFinished, this, [this, socket] {
        unmount(socket);
    });
}
