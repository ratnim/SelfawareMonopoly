#pragma once

#include <actions/action.h>

class CreateAccount : public Action
{
public:
    void handle(const QJsonValue& body) override;

protected:
    static QString answer(const QString& userSession);
};
