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
    connect(ClientSocket, SIGNAL(error(QAbstractSocket::SocketError)), this,
            SLOT(client_Error(QAbstractSocket::SocketError)));



    game_obj = obj;

}


// Common functions


void network_core::gameRestart()
{
    game_obj->player_0.clear();
    game_obj->player_X.clear();

    gameInit();
}




void network_core::gameInit()
{


    game_obj->playerType = game_obj->randomBetween();

    if(game_obj->playerType == 0)
    {
        amIcross = false;
        emit opponentMove();
        sendToClient(socket, "#youre_X");   // I`am 'zero', you re 'cross'
    }

    if(game_obj->playerType == 1)
    {
        amIcross = true;
        emit yourMove();
        sendToClient(socket, "#youre_0");   // I`am 'cross', you re 'zero'
    }



}

void network_core::thisMoveMade(int ind)
{


    if(isItServer)
    {
        sendToClient(socket, QString::number(ind));

        if(game_obj->playerType == 1)
        {
            game_obj->nextMove(1, ind);
        }

        if(game_obj->playerType == 0)
        {
            game_obj->nextMove(0, ind);
        }


        if(game_obj->playerType == 0)              // Win-check
        {
            if(game_obj->whoIsWin() == 0)
            {
                emit youWin();

                QTime time;
                time.start();
                for(int i(0); i < 15;)
                {
                    if(time.elapsed() > 5){
                        time.start();
                        ++i;
                    }
                }


                justsendToClient("#younot#");
                qDebug() << "You win!";
            }
            else if(game_obj->whoIsWin() == 1)
            {
                emit opponentWin();
                justsendToClient("#youwin#");
                qDebug() << "Your opponent win!";
            }else if(game_obj->whoIsWin() == 3)
            {
                emit draw();
                justsendToClient("#wedraw#");
                qDebug() << "Draw!";

            }
        }

        if(game_obj->playerType == 1)
        {
            if(game_obj->whoIsWin() == 1)
            {
                emit youWin();

                QTime time;
                time.start();
                for(int i(0); i < 15;)
                {
                    if(time.elapsed() > 5){
                        time.start();
                        ++i;
                    }
                }


                justsendToClient("#younot#");
                qDebug() << "You win!";
            }
            else if(game_obj->whoIsWin() == 0)
            {
                emit opponentWin();
                justsendToClient("#youwin#");
                qDebug() << "Your opponent win!";
            }else if(game_obj->whoIsWin() == 3)
            {
                emit draw();
                justsendToClient("#wedraw#");
                qDebug() << "Draw!";
            }
        }



        if(game_obj->whoIsWin() == 2)
            emit opponentMove();

    }
    else
    {
        client_sendToServer(QString::number(ind));
        emit opponentMove();
    }
}

bool network_core::isIcross()
{
    return amIcross;
}





// Server functions


void network_core::slotListen()
{
    startBroadcasting();

    isItServer = true;

    if(!server->listen(QHostAddress::Any, Port))
    {
        qDebug() << "Cant start the server: " << server->errorString();
        server->close();
        return;
    }
}

void network_core::slotNewConnection()
{
    isConnectedOnServer = true;
    server_timer.stop();
    serverUdpSocket->deleteLater();



    socket = server->nextPendingConnection();

    connect(socket, SIGNAL(disconnected()), this, SLOT(server_stop()));

    connect(socket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));


    emit serverConnectedState();


    //sendToClient(socket, game_obj->PlayerName);



}

void network_core::slotReadClient()
{
    qDebug() << "Читаем клиента: ";
    socket = (QTcpSocket*)sender();

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString message = codec->toUnicode(socket->readAll());

    qDebug() << "Message received from client: " + message;

    if(message.length() > 1)
    {
        qDebug() << "Name detected from message: " + message;

        game_obj->OpponentName = message;
        justsendToClient(game_obj->PlayerName);

        gameInit();

    }



    if(message.length() == 1)
    {
        CellToChange = message.toInt();

        qDebug() << "Клиент просит изменить клетку №: " + message;


        if(game_obj->playerType == 1)
        {
            switch (CellToChange) {
            case 0:
                emit set_0_on_0();
                break;
            case 1:
                emit set_0_on_1();
                break;
            case 2:
                emit set_0_on_2();
                break;
            case 3:
                emit set_0_on_3();
                break;
            case 4:
                emit set_0_on_4();
                break;
            case 5:
                emit set_0_on_5();
                break;
            case 6:
                emit set_0_on_6();
                break;
            case 7:
                emit set_0_on_7();
                break;
            case 8:
                emit set_0_on_8();
                break;

            default:
                break;
            }

        }

        if(game_obj->playerType == 0)
        {
            switch (CellToChange) {
            case 0:
                emit set_X_on_0();
                break;
            case 1:
                emit set_X_on_1();
                break;
            case 2:
                emit set_X_on_2();
                break;
            case 3:
                emit set_X_on_3();
                break;
            case 4:
                emit set_X_on_4();
                break;
            case 5:
                emit set_X_on_5();
                break;
            case 6:
                emit set_X_on_6();
                break;
            case 7:
                emit set_X_on_7();
                break;
            case 8:
                emit set_X_on_8();
                break;

            default:
                break;
            }


        }







        if(game_obj->playerType == 0)
        {
            game_obj->nextMove(1, CellToChange);
        }
        if(game_obj->playerType == 1)
        {
            game_obj->nextMove(0, CellToChange);
        }



        if(game_obj->playerType == 0)              // Win-check
        {
            if(game_obj->whoIsWin() == 0)
            {
                emit youWin();

                QTime time;
                time.start();
                for(int i(0); i < 15;)
                {
                    if(time.elapsed() > 5){
                        time.start();
                        ++i;
                    }
                }


                justsendToClient("#younot#");
                qDebug() << "You win!";
            }
            else if(game_obj->whoIsWin() == 1)
            {
                emit opponentWin();
                justsendToClient("#youwin#");
                qDebug() << "Your opponent win!";
            }else if(game_obj->whoIsWin() == 3)
            {
                emit draw();
                justsendToClient("#wedraw#");
                qDebug() << "Draw!";
            }
        }

        if(game_obj->playerType == 1)
        {
            if(game_obj->whoIsWin() == 1)
            {
                emit youWin();


                QTime time;
                time.start();
                for(int i(0); i < 15;)
                {
                    if(time.elapsed() > 5){
                        time.start();
                        ++i;
                    }
                }

                justsendToClient("#younot#");
                qDebug() << "You win!";
            }
            else if(game_obj->whoIsWin() == 0)
            {
                emit opponentWin();
                justsendToClient("#youwin#");
                qDebug() << "Your opponent win!";
            }else if(game_obj->whoIsWin() == 3)
            {
                emit draw();
                justsendToClient("#wedraw#");
                qDebug() << "Draw!";
            }
        }


        // if(game_obj->playerType != 1 || game_obj->playerType != 0)
        if(game_obj->whoIsWin() == 2) emit yourMove();


    }


}



void network_core::justsendToClient(QString str)
{
    //socket->waitForBytesWritten();
    //socket->waitForReadyRead(80);
    sendToClient(socket, str);
}

void network_core::sendToClient(QTcpSocket *socket, const QString &str)
{
    socket->write(str.toUtf8());
    socket->waitForBytesWritten();

}



void network_core::startBroadcasting()
{
    server_timer.start(700);
}

void network_core::broadcastDatagram()
{
    //qDebug() << QString::number(game_obj->randomBetween());

    QString ip;

    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address !=
                QHostAddress(QHostAddress::LocalHost)){
            ip = address.toString();

            qDebug() << "ip: " << ip;
        }
    }

    QByteArray server_datagram;

    server_datagram = "tic-tac_" + ip.toUtf8();


    serverUdpSocket->writeDatagram(server_datagram, QHostAddress::Broadcast, 4243);
}

void network_core::server_stop()
{
    socket->deleteLater();
    server->disconnect();
    // server->deleteLater();
    server->close();
    qDebug() << "on disconnected";

}

bool network_core::isServerConnect()
{
    return isConnectedOnServer;
}

bool network_core::amIServer()
{
    return isItServer;
}

























// Client functions


void network_core::client_connect()
{
    ClientSocket->connectToHost(serverIP, Port);
}

void network_core::client_readyRead()
{

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    //ClientSocket->waitForReadyRead()
    QString message = codec->toUnicode(ClientSocket->readAll());

    qDebug() << "Message from server: " + message;


    QString name;

    if(message.length() > 1)
    {


        for(auto &ch:message)
        {
            if(ch == '#') break;
            name += ch;
        }

        QString restOfMsg;

        if(name.length() > 1)
        {
            game_obj->OpponentName = name;

            qDebug() << "Name from opponent message: " + name;

            restOfMsg = message.mid(name.length(), 8);
        }else {
            restOfMsg = message;
        }



        if(restOfMsg == "#youre_X"){
            qDebug() << "Server set my type as: " + restOfMsg;
            game_obj->playerType = 1;
            amIcross = true;
            //if(game_obj->whoIsWin() == 2)
            emit yourMove();
        }
        if(restOfMsg == "#youre_0"){
            qDebug() << "Server set my type as: " + restOfMsg;
            game_obj->playerType = 0;
            amIcross = false;
            //if(game_obj->whoIsWin() == 2)
            emit opponentMove();
        }
        if(restOfMsg == "#youwin#")
        {
            qDebug() << "Received status: " + restOfMsg;
            emit youWin();
        }
        if(restOfMsg == "#younot#")
        {
            qDebug() << "Received status: " + restOfMsg;
            emit opponentWin();
        }
        if(restOfMsg == "#wedraw#")
        {
            emit draw();
            qDebug() << "Received status: " + restOfMsg;
        }
    }




    if(message.length() == 1)
    {
        CellToChange = message.toInt();

        qDebug() << "Server required to change: " + message;

        if(game_obj->playerType == 1)
        {
            //game_obj->nextMove(0, CellToChange);

            switch (CellToChange) {
            case 0:
                emit set_0_on_0();
                break;
            case 1:
                emit set_0_on_1();
                break;
            case 2:
                emit set_0_on_2();
                break;
            case 3:
                emit set_0_on_3();
                break;
            case 4:
                emit set_0_on_4();
                break;
            case 5:
                emit set_0_on_5();
                break;
            case 6:
                emit set_0_on_6();
                break;
            case 7:
                emit set_0_on_7();
                break;
            case 8:
                emit set_0_on_8();
                break;

            default:
                break;
            }

        }

        if(game_obj->playerType == 0)
        {
            //game_obj->nextMove(1, CellToChange);
            switch (CellToChange) {
            case 0:
                emit set_X_on_0();
                break;
            case 1:
                emit set_X_on_1();
                break;
            case 2:
                emit set_X_on_2();
                break;
            case 3:
                emit set_X_on_3();
                break;
            case 4:
                emit set_X_on_4();
                break;
            case 5:
                emit set_X_on_5();
                break;
            case 6:
                emit set_X_on_6();
                break;
            case 7:
                emit set_X_on_7();
                break;
            case 8:
                emit set_X_on_8();
                break;

            default:
                break;
            }


        }


        /////  Following block of code is under the question...
        ///
        /// if(game_obj->playerType == 0)
        /// {
        ///
        ///     if(game_obj->whoIsWin() == 0)
        ///         qDebug() << "You win!";
        ///     else if(game_obj->whoIsWin() == 1)
        ///         qDebug() << "Your opponent win!";
        /// }
        ///
        /// if(game_obj->playerType == 1)
        /// {
        ///     if(game_obj->whoIsWin() == 1)
        ///         qDebug() << "You win!";
        ///     else if(game_obj->whoIsWin() == 0)
        ///         qDebug() << "Your opponent win!";
        /// }
        ///
        /// //if(game_obj->playerType != 1 || game_obj->playerType != 0)



        /* if(game_obj->whoIsWin() == 2) */
        emit yourMove();


    }



}

void network_core::client_sendToServer(const QString &msg)
{
    ClientSocket->write(msg.toUtf8());
    // ClientSocket->waitForBytesWritten();
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
    qDebug() << "client_Connected() slot";
    isConnected = true;
    client_sendToServer(game_obj->PlayerName);
}

bool network_core::client_is_Connected()
{
    return isConnected;
}

void network_core::client_disconnect()
{
    ClientSocket->disconnectFromHost();
}

void network_core::client_Find()
{

    clientUdpSocket->bind(4243, QUdpSocket::ShareAddress);

}

void network_core::processPendingDatagrams()
{
    QByteArray client_datagram;
    while (clientUdpSocket->hasPendingDatagrams()) {
        client_datagram.resize(int(clientUdpSocket->pendingDatagramSize()));
        clientUdpSocket->readDatagram(client_datagram.data(), client_datagram.size());

        //qDebug() << "Received datagram: " << client_datagram.data();

        QString t_serverIP = client_datagram.data();
        if(t_serverIP.mid(0, 7) == "tic-tac")
        {
            serverIP = t_serverIP.mid(8);
            client_connect();
            clientUdpSocket->deleteLater();

        }

        // qDebug() << serverIP;

    }
}











































































