#pragma once

#include <QString>

class Player
{
public:
    Player(const QString& playerName);

	void nextTurn();

	void jail();
	bool inJail() const;
    void leaveJail();
	
	void move(int distance);
    int position() const;
    const QString& name() const;

	int timesRolled() const;
    void rolled();

protected:
	const QString m_name;
    int m_timesRolled = 0;
    int m_jailTurns = 0;
    int m_position = 0;
};

