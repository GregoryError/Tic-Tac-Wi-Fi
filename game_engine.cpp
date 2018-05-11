 #include "game_engine.h"

game_engine::game_engine(QObject *parent) : QObject(parent)
{

}

QString game_engine::showPlayerName()
{
    return PlayerName;
}

void game_engine::setPlayerName(QString name)
{
    PlayerName = name;
}

void game_engine::nextMove(int field)
{

}

int game_engine::whoIsWin()
{

}
