#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <QObject>
#include <QString>

class game_engine : public QObject
{
    Q_OBJECT
public:
    game_engine(QObject *parent = nullptr);
    QString PlayerName;
    QString OpponentName;


private:



signals:

public slots:
    QString showPlayerName();
    QString showOpponentName();
    void setPlayerName(QString name);
    void nextMove(int field);
    int whoIsWin();
};

#endif // GAME_ENGINE_H
