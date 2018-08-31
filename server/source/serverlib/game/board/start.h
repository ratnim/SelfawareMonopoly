#pragma once 

#include <game/board/field.h>

class game;

class Start : public Field
{
public:
    Start(const QString& name);

	void passBy(const QString& playerName, Game* game) override;

protected:
    const int moneyFromStart = 200;
};