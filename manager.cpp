#include "manager.h"


manager::manager(QQmlContext *cont, QObject *parent) : QObject(parent)
{
    game = new game_engine;
    net = new network_core(game, 4242);

    cont->setContextProperty("network_core", net);
    cont->setContextProperty("game_engine", game);
}
