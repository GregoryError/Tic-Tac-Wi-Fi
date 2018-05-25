#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QDebug>
#include <QSet>

#include <QSoundEffect>

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

    QSoundEffect *effect_win, *effect_loose, *effect_tap, *effect_begin;


private:



signals:


public slots:
    QString showPlayerName();
    QString showOpponentName();
    void setPlayerName(QString name);
    void nextMove(const int& player, const int& field);
    int whoIsWin();
    int randomBetween();

    void soundWin();
    void soundLoose();
    void soundBegin();
    void soundTap();



};

#endif // GAME_ENGINE_H
