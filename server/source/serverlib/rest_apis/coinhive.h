
#include <QString>
#include <QTimer>
#include <QNetworkReply>

namespace rest_apis
{

namespace coinhive
{

class MiningSupervisor : public QObject
{
    Q_OBJECT

public:
    MiningSupervisor(const size_t intervalSecs);

public slots:
    void onTimer();

signals:
    void userMined(const QString& userName, size_t amount);

protected:
    void onTopReply(QNetworkReply * reply);
    void onWithdrawReply(QNetworkReply * reply);

protected:
    QTimer m_timer;
};

QNetworkReply * requestTop();
QNetworkReply * requestWithdraw(const QString& userName, const size_t amount);

}

} // namespace rest_apis
