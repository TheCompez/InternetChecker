#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QTimer>

namespace Network {

  class Internet;
  /**
* @brief The Internet class
*/
  class Internet : public QObject {

    Q_OBJECT

  public:
    Internet();
    ~Internet();

    Q_INVOKABLE void checkInternet(const QUrl &url);
    Q_INVOKABLE bool getStatus() const ;

  private:
    bool m_status;

    QNetworkAccessManager manager;

  };

  class Timeout : public QObject {

    Q_OBJECT

  public:
    Timeout(QNetworkReply* reply, const int timeout) : QObject(reply) {
      Q_ASSERT(reply);
      if (reply) {
          QTimer::singleShot(timeout, this, SLOT(timeout()));
        }
    }
    ~Timeout() {}

  private slots:
    void timeout() {
      QNetworkReply* reply = static_cast<QNetworkReply*>(parent());
      if (reply->isRunning()) {
          qDebug() << "Timedout!";
          reply->close();
        }
    }
  };

}

#endif // NETWORK_H
