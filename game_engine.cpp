 #include "game_engine.h"

game_engine::game_engine(QObject *parent) : QObject(parent)
{

}

void game_engine::setPlayerName(QString name)
{
    PlayerName = name;
}
