#pragma once

#include <game/board/field.h>

class GoToJail : public Field
{
public:
    GoToJail(const QString& name);

    bool moveOn(const QString& playerName, Game* game) override;
};
