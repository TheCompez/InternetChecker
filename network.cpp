#include "network.h"

using namespace Network;

Internet::Internet() {

}

Internet::~Internet() {

}

void Internet::checkInternet(const QUrl &url) {

  QNetworkRequest request(QUrl(url.toString()));
  QNetworkReply *reply = manager.get(request);
  new Timeout(reply, 3000);

  QEventLoop loop;
  QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
  loop.exec();

  if(reply->error() == QNetworkReply::NoError) {

      reply->bytesAvailable() ?  m_status = true : m_status = false;
      qDebug() << "Connected!";
    } else {
      qDebug() << "Disconnected!";
      m_status = false;
    }

  reply->deleteLater();

}

bool Internet::getStatus() const {
  return m_status;
}
