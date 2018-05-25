#ifndef NETWORK_CORE_H
#define NETWORK_CORE_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QString>
#include <QDebug>
#include <QTimer>
#include <QTextCodec>


#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>

#include "game_engine.h"

class network_core : public QObject
{
    Q_OBJECT
public:
    explicit network_core(game_engine *obj, const int &nPort, QObject *parent = nullptr);
    QString PlayerNm;

    game_engine *game_obj = nullptr;

    int CellToChange = 0;

    bool isItServer = false;

    bool amIcross = false;


private:
    QTcpServer *server;
    QTcpSocket *socket;
    int Port;
    void sendToClient(QTcpSocket *socket, const QString &str);

    QUdpSocket *serverUdpSocket = nullptr;   // for broadcasting purposes
    QUdpSocket *clientUdpSocket = nullptr;

    QTimer server_timer;
    QString serverIP;



private:      // client
    QTcpSocket *ClientSocket;
    bool isConnected = false;
    bool isConnectedOnServer = false;



signals:
    void serverConnectedState();
    void clientConnectedState();

    void opponentMove();
    void yourMove();

    void opponentWin();
    void youWin();


    // gamefield managing:

    void set_X_on_0();
    void set_X_on_1();
    void set_X_on_2();
    void set_X_on_3();
    void set_X_on_4();
    void set_X_on_5();
    void set_X_on_6();
    void set_X_on_7();
    void set_X_on_8();

    void set_0_on_0();
    void set_0_on_1();
    void set_0_on_2();
    void set_0_on_3();
    void set_0_on_4();
    void set_0_on_5();
    void set_0_on_6();
    void set_0_on_7();
    void set_0_on_8();


public slots:
    virtual void slotNewConnection();
    void slotReadClient();
    void slotListen();
    void server_stop();
    bool isServerConnect();
    bool amIServer();
    void justsendToClient(QString str);

    void startBroadcasting();
    void broadcastDatagram();

    void processPendingDatagrams();


    void client_connect();
    void client_readyRead();
    void client_Connected();

    void client_Find();
    void client_Error(QAbstractSocket::SocketError);
    void client_sendToServer(const QString &msg);
    bool client_is_Connected();
    void client_disconnect();


    void gameInit();
    void thisMoveMade(int ind);
    bool isIcross();


    void gameRestart();



};

#endif // NETWORK_CORE_H





















































