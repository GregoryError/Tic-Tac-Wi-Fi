#ifndef NETWORK_CORE_H
#define NETWORK_CORE_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QDebug>
#include <QTimer>
#include <QTime>


#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>

#include "game_engine.h"

class network_core : public QObject
{
    Q_OBJECT
public:
    explicit network_core(game_engine *obj, const int &nPort, QObject *parent = nullptr);
    QString PlayerNm;

private:
    QTcpServer *server;
    QTcpSocket *socket;
    int Port;
    void sendToClient(QTcpSocket *socket, const QString &str);

private:      // client
    QTcpSocket *ClientSocket;
    QList<QHostAddress> myIpAddresses;
    bool isConnected = false;
    bool isConnectedOnServer = false;

    QString test_ip;






signals:
    void serverConnectedState();


public slots:
    virtual void slotNewConnection();
    void slotReadClient();
    void slotListen();
    void server_stop();
    bool isServerConnect();



    QString test_showIp();
    void client_FindAndConnect();
    void client_readyRead();
    void client_Error(QAbstractSocket::SocketError);
    void client_sendToServer();
    void client_Connected();
    bool client_is_Connected();



};

#endif // NETWORK_CORE_H
