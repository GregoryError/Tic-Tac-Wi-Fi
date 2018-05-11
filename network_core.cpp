#include "network_core.h"



network_core::network_core(game_engine *obj, const int &nPort, QObject *parent)
{

    server = new QTcpServer(this);
    Port = nPort;
    connect(server, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));

    // client

    ClientSocket = new QTcpSocket(this);

    connect(ClientSocket, SIGNAL(connected()), SLOT(client_Connected()));
    connect(ClientSocket, SIGNAL(readyRead()), SLOT(client_readyRead()));
    connect(ClientSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(client_Error(QAbstractSocket::SocketError)));

    connect(server, SIGNAL(destroyed(QObject*)), SLOT(server_stop()));

    PlayerNm = obj->PlayerName;

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

void network_core::client_FindAndConnect()
{

    myIpAddresses = QNetworkInterface::allAddresses();

    QString local_ip = myIpAddresses[1].toString();

    QString temp;

    short itter(0);

    for(auto &ch:local_ip)
    {
        if(ch == '.')
            ++itter;
        if(itter == 3)
            break;
        temp += ch;
    }

    unsigned short beg = 0;

    QString possiblyServerAddress;

    QTime time;


    while(beg != 255)
    {
        ++beg;
        possiblyServerAddress = temp + "." + QString::number(beg);



        qDebug() << possiblyServerAddress;


        time.start();

        for(int i(0); i < 15;)
        {
            if(time.elapsed() > 15){
                time.start();
                ++i;
            }
        }

        if(isConnected)
            break;


        //ClientSocket->abort();


        test_ip = possiblyServerAddress;


        ClientSocket->connectToHost(possiblyServerAddress, Port);

        if(ClientSocket->waitForConnected(70))
           break;





        //ClientSocket->abort();    // Not sure about this
    }



}

void network_core::client_sendToServer()
{
    ClientSocket->write("I`am the client.");

}

void network_core::sendToClient(QTcpSocket *socket, const QString &str)
{
    socket->write(str.toUtf8());

}

















































































