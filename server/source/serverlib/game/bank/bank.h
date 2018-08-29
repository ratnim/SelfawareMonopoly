#pragma once

#include <map>

#include <QObject>
#include <QString>

class Bank : public QObject
{
    Q_OBJECT
public:
    void createAccount(const QString& name, int deposit = 0);
    void transferMoney(const QString& reciever, int amount);
    int balance(const QString& name) const;

signals:
    void onMoneyChange(const QString& playerName, int balance);

protected:
    std::map<QString, int> m_accounts;
};
