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

void game_engine::nextMove(int who, int field)
{
    QString str = QString::number(field);
    qDebug() << str;
}

int game_engine::whoIsWin()
{
    return 2;
    // still in game? return 2;
    // Here is a winner? return 0 / 1;
}


int game_engine::randomBetween()
{
    qsrand(QDateTime::currentMSecsSinceEpoch());
    return qrand() % 2; //((1 + 1) - 0) + 0);
}

