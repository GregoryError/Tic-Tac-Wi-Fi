#include "game_engine.h"


game_engine::game_engine(QObject *parent) : QObject(parent)
{
    effect_win = new QSoundEffect;
    effect_win->setSource(QUrl::fromLocalFile(":/win.wav"));
    effect_loose = new QSoundEffect;
    effect_loose->setSource(QUrl::fromLocalFile(":/loose.wav"));
    effect_begin = new QSoundEffect;
    effect_begin->setSource(QUrl::fromLocalFile(":/begin.wav"));
    effect_tap = new QSoundEffect;
    effect_tap->setSource(QUrl::fromLocalFile(":/tap.wav"));

}



void game_engine::soundWin()
{
    effect_win->play();
}

void game_engine::soundLoose()
{
    effect_loose->play();
}

void game_engine::soundBegin()
{
    effect_begin->play();
}

void game_engine::soundTap()
{
    effect_tap->play();
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

    short tempResult = -1;

    if(player_0.find(0) != player_0.end() &&
            player_0.find(1) != player_0.end() &&
            player_0.find(2) != player_0.end())
        tempResult = 0;
    if(player_0.find(3) != player_0.end() &&
            player_0.find(4) != player_0.end() &&
            player_0.find(5) != player_0.end())
        tempResult = 0;
    if(player_0.find(6) != player_0.end() &&
            player_0.find(7) != player_0.end() &&
            player_0.find(8) != player_0.end())
        tempResult = 0;
    if(player_0.find(0) != player_0.end() &&
            player_0.find(3) != player_0.end() &&
            player_0.find(6) != player_0.end())
        tempResult = 0;
    if(player_0.find(1) != player_0.end() &&
            player_0.find(4) != player_0.end() &&
            player_0.find(7) != player_0.end())
        tempResult = 0;
    if(player_0.find(2) != player_0.end() &&
            player_0.find(5) != player_0.end() &&
            player_0.find(8) != player_0.end())
        tempResult = 0;
    if(player_0.find(6) != player_0.end() &&
            player_0.find(4) != player_0.end() &&
            player_0.find(2) != player_0.end())
        tempResult = 0;
    if(player_0.find(0) != player_0.end() &&
            player_0.find(4) != player_0.end() &&
            player_0.find(8) != player_0.end())
        tempResult = 0;


    if(player_X.find(0) != player_X.end() &&
            player_X.find(1) != player_X.end() &&
            player_X.find(2) != player_X.end())
        tempResult = 1;
    if(player_X.find(3) != player_X.end() &&
            player_X.find(4) != player_X.end() &&
            player_X.find(5) != player_X.end())
        tempResult = 1;
    if(player_X.find(6) != player_X.end() &&
            player_X.find(7) != player_X.end() &&
            player_X.find(8) != player_X.end())
        tempResult = 1;
    if(player_X.find(0) != player_X.end() &&
            player_X.find(3) != player_X.end() &&
            player_X.find(6) != player_X.end())
        tempResult = 1;
    if(player_X.find(1) != player_X.end() &&
            player_X.find(4) != player_X.end() &&
            player_X.find(7) != player_X.end())
        tempResult = 1;
    if(player_X.find(2) != player_X.end() &&
            player_X.find(5) != player_X.end() &&
            player_X.find(8) != player_X.end())
        tempResult = 1;
    if(player_X.find(6) != player_X.end() &&
            player_X.find(4) != player_X.end() &&
            player_X.find(2) != player_X.end())
        tempResult = 1;
    if(player_X.find(0) != player_X.end() &&
            player_X.find(4) != player_X.end() &&
            player_X.find(8) != player_X.end())
        tempResult = 1;



    if(tempResult == 0)
        return 0;
    if(tempResult == 1)
        return 1;
    if(tempResult == -1)
        if(player_0.count() + player_X.count() == 9)
            return 3; // This means nobody win

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
    qDebug() << "Добавленно в набор для игрока " +
                QString::number(player) + ": " + str;


}

































