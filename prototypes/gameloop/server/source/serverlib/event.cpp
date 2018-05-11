#include "event.h"

#include <QJsonDocument>
#include <QUrl>

std::unique_ptr<Event> Event::fromString(const QByteArray& data)
{
    //QUrl::from
    auto json = QJsonDocument::fromJson(data);
    return nullptr;
}

void EnterEvent::handle(GameState& state)
{

}