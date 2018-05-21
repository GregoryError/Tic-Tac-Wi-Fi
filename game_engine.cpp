#include "game_engine.h"


game_engine::game_engine(QObject *parent) : QObject(parent)
{

}

QString game_engine::showPlayerName()
{
    return PlayerName;
}

QString game_engine::showOpponentName()
{
    return OpponentName;
}

void game_engine::setPlayerName(QString name)
{
    PlayerName = name;
}

int game_engine::whoIsWin()
{
    // still in game? return 2;
    // Here is a winner? return 0 / 1;

    if(player_0.find(0) != player_0.end() &&
            player_0.find(1) != player_0.end() &&
            player_0.find(2) != player_0.end())
        return 0;
    if(player_0.find(3) != player_0.end() &&
            player_0.find(4) != player_0.end() &&
            player_0.find(5) != player_0.end())
        return 0;
    if(player_0.find(6) != player_0.end() &&
            player_0.find(7) != player_0.end() &&
            player_0.find(8) != player_0.end())
        return 0;
    if(player_0.find(0) != player_0.end() &&
            player_0.find(3) != player_0.end() &&
            player_0.find(6) != player_0.end())
        return 0;
    if(player_0.find(1) != player_0.end() &&
            player_0.find(4) != player_0.end() &&
            player_0.find(7) != player_0.end())
        return 0;
    if(player_0.find(2) != player_0.end() &&
            player_0.find(5) != player_0.end() &&
            player_0.find(8) != player_0.end())
        return 0;
    if(player_0.find(6) != player_0.end() &&
            player_0.find(4) != player_0.end() &&
            player_0.find(2) != player_0.end())
        return 0;
    if(player_0.find(0) != player_0.end() &&
            player_0.find(4) != player_0.end() &&
            player_0.find(8) != player_0.end())
        return 0;


    if(player_X.find(0) != player_X.end() &&
            player_X.find(1) != player_X.end() &&
            player_X.find(2) != player_X.end())
        return 1;
    if(player_X.find(3) != player_X.end() &&
            player_X.find(4) != player_X.end() &&
            player_X.find(5) != player_X.end())
        return 1;
    if(player_X.find(6) != player_X.end() &&
            player_X.find(7) != player_X.end() &&
            player_X.find(8) != player_X.end())
        return 1;
    if(player_X.find(0) != player_X.end() &&
            player_X.find(3) != player_X.end() &&
            player_X.find(6) != player_X.end())
        return 1;
    if(player_X.find(1) != player_X.end() &&
            player_X.find(4) != player_X.end() &&
            player_X.find(7) != player_X.end())
        return 1;
    if(player_X.find(2) != player_X.end() &&
            player_X.find(5) != player_X.end() &&
            player_X.find(8) != player_X.end())
        return 1;
    if(player_X.find(6) != player_X.end() &&
            player_X.find(4) != player_X.end() &&
            player_X.find(2) != player_X.end())
        return 1;
    if(player_X.find(0) != player_X.end() &&
            player_X.find(4) != player_X.end() &&
            player_X.find(8) != player_X.end())
        return 1;


    return 2;
}


int game_engine::randomBetween()
{
    qsrand(QDateTime::currentMSecsSinceEpoch());
    return qrand() % 2;
}

void game_engine::nextMove(const int& player, const int& field)
{
    if(player == 0)
        player_0.insert(field);
    if(player == 1)
        player_X.insert(field);

    QString str = QString::number(field);
    qDebug() << str;


}

