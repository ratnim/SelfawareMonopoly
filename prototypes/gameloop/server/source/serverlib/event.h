#pragma once

#include <QString>

#include <memory>

#include "gamestate.h"

class Event
{
public:
    static std::unique_ptr<Event> fromString(const QByteArray& data);

    virtual void handle(GameState& state) = 0;
};

class EnterEvent : public Event
{
    void handle(GameState& state) override;
};