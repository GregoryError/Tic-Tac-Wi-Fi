#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "network_core.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QQmlContext *cont;

    cont = engine.rootContext();

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    network_core *net = new network_core(4242);

    cont->setContextProperty("network_core", net);

    return app.exec();


}