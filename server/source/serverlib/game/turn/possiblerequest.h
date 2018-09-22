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
    static PossibleRequest endTurn();
    static PossibleRequest buyField();
    static PossibleRequest dontBuyField();
    static PossibleRequest constructBuilding(const QJsonArray& groups);
    static PossibleRequest payDebt(const QString& beneficiary, int amount);
    static PossibleRequest fileBankruptcy();

protected:
    const QString m_request;
    const QJsonObject m_data;
};