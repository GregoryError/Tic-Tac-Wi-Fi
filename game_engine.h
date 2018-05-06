#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <QObject>
#include <QString>

class game_engine : public QObject
{
    Q_OBJECT
public:
    explicit game_engine(QObject *parent = nullptr);


private:
    QString PlayerName;


signals:

public slots:
    void setPlayerName(QString name);
    void nextMove(int field);
    int whoIsWin();
};

#endif // GAME_ENGINE_H
