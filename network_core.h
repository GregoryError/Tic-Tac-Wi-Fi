#ifndef NETWORK_CORE_H
#define NETWORK_CORE_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QString>
#include <QDebug>
#include <QTimer>
#include <QTime>
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

private:
    QTcpServer *server;
    QTcpSocket *socket;
    int Port;
    void sendToClient(QTcpSocket *socket, const QString &str);

    QUdpSocket *serverUdpSocket = nullptr;
    QUdpSocket *clientUdpSocket = nullptr;

    QTimer server_timer;
    QString serverIP;



private:      // client
    QTcpSocket *ClientSocket;
    QList<QHostAddress> myIpAddresses;
    bool isConnected = false;
    bool isConnectedOnServer = false;

    QString test_ip;






signals:
    void serverConnectedState();
    void clientConnectedState();

   void opponentMove();
   void yourMove();

   void opponentWin();
   void youWin();


public slots:
    virtual void slotNewConnection();
    void slotReadClient();
    void slotListen();
    void server_stop();
    bool isServerConnect();

    void startBroadcasting();
    void broadcastDatagram();

    void processPendingDatagrams();


    QString test_showIp();

    void client_connect();
    void client_Find();
    void client_readyRead();
    void client_Error(QAbstractSocket::SocketError);
    void client_sendToServer(const QString &msg);
    void client_Connected();
    bool client_is_Connected();

    void tellClientToMove();
    void gameProcess();



};

#endif // NETWORK_CORE_H





















































