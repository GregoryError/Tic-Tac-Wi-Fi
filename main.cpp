#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>


//#include "network_core.h"
//#include "game_engine.h"
#include "manager.h"

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

    manager *top = new manager(cont);

    Q_UNUSED(top);

    return app.exec();


}
