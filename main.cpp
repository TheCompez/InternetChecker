#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "network.h"

using namespace Network;

int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  Internet internet;
  //internet.checkInternet(QUrl("http://google.com")); //setURL for check the status

  QQmlApplicationEngine engine;

  QQmlContext *context = engine.rootContext();
  context->setContextProperty("Internet", &internet);

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
