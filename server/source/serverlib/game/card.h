
#pragma once

#include <functional>

#include <QString>


class Game;

struct Card
{
    Card(std::function<bool(Game&)> _effect, const QString& _description)
    : effect(_effect)
    , description(_description)
    {}

    std::function<bool(Game&)> effect; // Allow lambdas for arbitrary effects, returns if it changed state by itself
    const QString description;
};
