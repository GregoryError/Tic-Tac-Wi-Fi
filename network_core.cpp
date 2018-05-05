#include "network_core.h"



network_core::network_core(const int &nPort, QObject *parent)
{
    server = new QTcpServer(this);
    Port = nPort;
    connect(server, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));

    // client

    ClientSocket = new QTcpSocket(this);

    connect(ClientSocket, SIGNAL(connected()), SLOT(client_Connected()));
    connect(ClientSocket, SIGNAL(readyRead()), SLOT(client_readyRead()));
    connect(ClientSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(client_Error(QAbstractSocket::SocketError)));

}


void network_core::slotNewConnection()
{
    socket = server->nextPendingConnection();

    connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));

    sendToClient(socket, "Connected!");


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

void network_core::server_stop()
{

    server->deleteLater();

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


    while(beg != 255)
    {

        possiblyServerAddress = temp + "." + QString::number(beg);
        ++beg;
        qDebug() << possiblyServerAddress;
        ClientSocket->connectToHost(possiblyServerAddress, Port);
        ClientSocket->waitForConnected(90);

        QTime time;
        time.start();

        for(int i(0); i < 11;)
        {
            if(time.elapsed() > 9){
                time.start();
                ++i;
            }
        }

        if(isConnected)
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

















































































