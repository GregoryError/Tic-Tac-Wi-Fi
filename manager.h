#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QQmlContext>
#include "network_core.h"
#include "game_engine.h"

class manager : public QObject
{
    Q_OBJECT
public:
    explicit manager(QQmlContext *cont, QObject *parent = nullptr);
    game_engine *game;
    network_core *net;

signals:

public slots:
};

#endif // MANAGER_H
