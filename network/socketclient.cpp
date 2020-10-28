#include "socketclient.h"


SocketClient::SocketClient(QObject *parent) :
    QObject(parent)
{

}

void SocketClient::setSocket()
{
    socket = new QTcpSocket(this);

    connect(socket,SIGNAL(connected()), this, SLOT(connected()));
    connect(socket,SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket,SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket,SIGNAL(bytesWritten(qint64)),this,SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(error()));

    qDebug() << "Connecting...";

    // Server IP -> We will insert it in command line before launch the program
    socket->connectToHost("127.0.0.1",1800);

}

void SocketClient::closeSocket()
{
    socket->close();

}

void SocketClient::connected()
{
    if(!socket->waitForConnected(5000)){
        qDebug() << "Error: " <<  socket->errorString();

    }

    else {
        qInfo()<<"Connected";
    }
}


// Disconnected
void SocketClient::disconnected()
{
    qDebug() << "Disconnected!";
}


// Finished of writing all data in buffer
void SocketClient::bytesWritten (qint64 bytes)
{
}



// Read from socket
void SocketClient::readyRead()
{
    if(!sender()) return;
    QDataStream socketStream(socket);

    socketStream.setVersion(QDataStream::Qt_5_12);

    Header header;
    User userMessage;
    // Start to read the message
    socketStream.startTransaction();


    socketStream >> header;
    switch(header.getType())
    {

        case MessageType::S_REGISTER_OK:{
            qDebug() << "Received: S_REGISTER_OK";
            if (!socketStream.commitTransaction())
                return;

             emit registrationOK(userData);
             break;
        }
        case MessageType::S_REGISTER_KO:{
            qDebug() << "Received: S_REGISTER_KO";
            if (!socketStream.commitTransaction())
                return;
            emit registrationKO();
            break;
        }
        case MessageType::S_ERROR_DB:{
            qDebug() << "Received: S_ERROR_DB";
            if (!socketStream.commitTransaction())
                return;
            emit errorDB();
            break;
        }
        case MessageType::S_LOGIN_OK:{
            qDebug() << "Received: S_LOGIN_OK";
            socketStream>>userMessage;
            if (!socketStream.commitTransaction())
                return;
            emit loginOK(userMessage);
            break;
        }
        case MessageType::S_LOGIN_KO:{
            qDebug() << "Received: S_LOGIN_KO";
            if (!socketStream.commitTransaction())
                return;
            emit loginKO();
            break;
        }
        case MessageType::S_INPUT_KO:{
            qDebug() << "Received: S_INPUT_KO";
            //Old psw not correct
            if (!socketStream.commitTransaction())
                return;
            emit errorOldPwd();
            break;
        }
        case MessageType::S_NOT_LOGGED:{
            qDebug() << "Received: S_NOT_LOGGED";
            if (!socketStream.commitTransaction())
                return;
            emit notLogged();
            break;
        }
        case MessageType::S_UPD_KO:{
            qDebug() << "Received: S_UPD_KO";
            if (!socketStream.commitTransaction())
                return;
            emit updateKO();

            break;
        }

        case MessageType::S_UPD_OK:{
            qDebug() << "Received: S_UPD_OK";
            if (!socketStream.commitTransaction())
                return;
            emit updateOK(userData);
            break;
        }

        default:{
            qDebug() << "Unknown MessageTyps: wait for more data";
            if (!socketStream.commitTransaction())
                return;     // wait for more data
        }
    }
}

void SocketClient::registrationMessage(User userRegistration){


    Header haederReg(MessageType::C_REGISTER) ;
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_12);
    clientStream << haederReg << userRegistration;
    qDebug() << "Sent: C_REGISTER";
}

void SocketClient::loginMessage(User userLogin)
{
    Header haederReg(MessageType::C_LOGIN) ;
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_12);
    clientStream << haederReg << userLogin;
    qDebug() << "Sent: C_LOGIN";
}

void SocketClient::updateImage(User user)
{
    userData = user;
    Header haederReg(MessageType::C_UPD_IMG) ;
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_12);
    clientStream << haederReg << user;
    qDebug() << "Sent: C_UPD_IMG";
}

void SocketClient::updateName(User user)
{   
    Header haederReg(MessageType::C_UPD_NAME) ;
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_12);
    clientStream << haederReg << user;
    qDebug() << "Sent: C_UPD_NAME";
}

void SocketClient::updateSurname(User user)
{
    Header haederReg(MessageType::C_UPD_SURN) ;
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_12);
    clientStream << haederReg << user;
    qDebug() << "Sent: C_UPD_SURN";
}

void SocketClient::updatePassword(User user)
{
    Header haederReg(MessageType::C_UPD_PASS) ;
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_12);
    clientStream << haederReg << user;
    qDebug() << "Sent: C_UPD_PASS";
}

void SocketClient::error()
{
       emit errorServer();
}


