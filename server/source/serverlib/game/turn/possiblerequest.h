#pragma once

#include <QJsonObject>
#include <QString>

class PossibleRequest
{
public:
    PossibleRequest(const QString& request, const QJsonObject data = {});

	QJsonObject toJson() const;

	static PossibleRequest playerReady();
    static PossibleRequest gameStart();
    static PossibleRequest rollDice();

protected:
    const QString m_request;
    const QJsonObject m_data;
};