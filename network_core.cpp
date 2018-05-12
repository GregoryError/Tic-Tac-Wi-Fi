#include "network_core.h"



network_core::network_core(game_engine *obj, const int &nPort, QObject *parent)
{

    server = new QTcpServer(this);
    Port = nPort;
    connect(server, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));


    serverUdpSocket = new QUdpSocket(this);
    clientUdpSocket = new QUdpSocket(this);

    connect(&server_timer, &QTimer::timeout, this, &network_core::broadcastDatagram);




    connect(clientUdpSocket, SIGNAL(readyRead()),
                this, SLOT(processPendingDatagrams()));



    // client

    ClientSocket = new QTcpSocket(this);

    connect(ClientSocket, SIGNAL(connected()), SLOT(client_Connected()));
    connect(ClientSocket, SIGNAL(readyRead()), SLOT(client_readyRead()));
    connect(ClientSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(client_Error(QAbstractSocket::SocketError)));


    game_obj = obj;

    //PlayerNm = obj->PlayerName;

}


void network_core::client_Find()
{

  clientUdpSocket->bind(4243, QUdpSocket::ShareAddress);

}

void network_core::client_connect()
{
    ClientSocket->connectToHost(serverIP, Port);
}



void network_core::startBroadcasting()
{
    server_timer.start(500);
}

void network_core::broadcastDatagram()
{
    QString ip;

    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost)){
            ip = address.toString();

            qDebug() << "ip: " << ip;
        }
    }

    QByteArray server_datagram;

    server_datagram = "tic-tac_" + ip.toUtf8();


    serverUdpSocket->writeDatagram(server_datagram, QHostAddress::Broadcast, 4243);
}

void network_core::processPendingDatagrams()
{
    QByteArray client_datagram;
       while (clientUdpSocket->hasPendingDatagrams()) {
           client_datagram.resize(int(clientUdpSocket->pendingDatagramSize()));
           clientUdpSocket->readDatagram(client_datagram.data(), client_datagram.size());

           qDebug() << "Received datagram: " << client_datagram.data();

           QString t_serverIP = client_datagram.data();
           if(t_serverIP.mid(0, 7) == "tic-tac")
           {
              serverIP = t_serverIP.mid(8);
              client_connect();
              clientUdpSocket->deleteLater();

           }

           qDebug() << serverIP;

       }
}


void network_core::slotNewConnection()
{
    socket = server->nextPendingConnection();

    connect(socket, SIGNAL(disconnected()), this, SLOT(server_stop()));

    connect(socket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));

    //sendToClient(socket, "Connected!");

    sendToClient(socket, PlayerNm);

    isConnectedOnServer = true;

    emit serverConnectedState();

    qDebug() <<  "Someone just was connected.";


}


void network_core::server_stop()
{
      socket->deleteLater();
      server->disconnect();
   // server->deleteLater();
      server->close();
    qDebug() << "on disconnected";

}


void network_core::slotReadClient()
{
    socket = (QTcpSocket*)sender();
    qDebug() << socket->readAll();
}


void network_core::slotListen()
{
    startBroadcasting();

    if(!server->listen(QHostAddress::Any, Port))
    {
        qDebug() << "Cant start the server: " << server->errorString();
        server->close();
        return;
    }
}

void network_core::client_readyRead()
{

    qDebug() << ClientSocket->readAll();



    if(isConnected || isConnectedOnServer)
    {
        game_obj->PlayerName = ClientSocket->readAll();

    }


}

void network_core::client_Error(QAbstractSocket::SocketError err)
{
    QString strError =
            "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                             "The host wasn`t found." :
                             err == QAbstractSocket::RemoteHostClosedError ?
                                 "The remoute host is closed." :
                                 err == QAbstractSocket::ConnectionRefusedError ?
                                     "The connection was refused." :
                                     QString(ClientSocket->errorString()));
    qDebug() << strError;
}

void network_core::client_Connected()
{
    emit clientConnectedState();
    qDebug() << "Received the connected() signal.";
    isConnected = true;

}

bool network_core::client_is_Connected()
{
    return isConnected;
}



bool network_core::isServerConnect()
{
    return isConnectedOnServer;
}


QString network_core::test_showIp()
{
    return test_ip;
}


void network_core::client_sendToServer()
{
    ClientSocket->write("I`am the client.");

}

void network_core::sendToClient(QTcpSocket *socket, const QString &str)
{
    socket->write(str.toUtf8());

}

















































































