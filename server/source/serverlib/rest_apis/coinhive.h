
#include <QString>
#include <QTimer>
#include <QNetworkReply>

namespace rest_apis
{

namespace coinhive
{

const QString coinhiveAPIHost("https://api.coinhive.com");

class MiningSupervisor : public QObject
{
    Q_OBJECT

public:
    MiningSupervisor(const size_t intervalSecs = 60, const size_t blockSize = 1024, const QString& host = coinhiveAPIHost);

public slots:
    void onTimer();
    void onReplyError(QNetworkReply::NetworkError error);

signals:
    void userMined(const QString& userName, int amount);

protected:
    void onTopReply(QNetworkReply * reply);
    void onWithdrawReply(QNetworkReply * reply);

    QNetworkReply * requestTop();
    QNetworkReply * requestWithdraw(const QString& userName, const size_t amount);

protected:
    QTimer m_timer;
    QString m_host;
    QString m_key;
    size_t m_blockSize;
};

}

} // namespace rest_apis
