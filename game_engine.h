#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QDebug>
#include <QSet>

class game_engine : public QObject
{
    Q_OBJECT
public:
    game_engine(QObject *parent = nullptr);
    QString PlayerName;
    QString OpponentName;
    int playerType;   // sets who are you, cross or circle


    QSet<int> player_0;  // Sets for collecting player answers
    QSet<int> player_X;
private:



signals:


public slots:
    QString showPlayerName();
    QString showOpponentName();
    void setPlayerName(QString name);
    void nextMove(const int& player, const int& field);
    int whoIsWin();
    int randomBetween();



};

#endif // GAME_ENGINE_H
