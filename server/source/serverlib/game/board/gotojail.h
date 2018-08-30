#pragma once

#include <game/board/field.h>

class GoToJail : public Field
{
public:
    GoToJail(const QString& name);

	bool moveOnTriggersStateChange(const QString& playerName) const override;
    void moveOn(const QString& playerName, Game* game) override;
};
