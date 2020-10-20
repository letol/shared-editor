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

    qDebug() << "Connecting...";

    // Server IP -> We will insert it in command line before launch the program
    socket->connectToHost("127.0.0.1",1800);

    if(!socket->waitForConnected(5000))
    {
       qDebug() << "Error: " <<  socket->errorString();
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
    qInfo() << "we wrote: " << bytes;
}



// Read from socket
void SocketClient::readyRead()
{
    if(!sender()) return;
    QDataStream socketStream(socket);

    socketStream.setVersion(QDataStream::Qt_5_12);

    Header header;
    User userMessage;
    socketStream >> header;

    QByteArray image;

    switch(header.getType())
    {

        case MessageType::S_REGISTER_OK:{

         emit registrationOK(userData);
            break;
        }
        case MessageType::S_REGISTER_KO:{
            emit registrationKO();
            break;
        }
        case MessageType::S_ERROR_DB:{
            emit errorDB();
            break;
        }
        case MessageType::S_LOGIN_OK:{

            socketStream >> userMessage;
            qDebug()<< "received: " << userMessage.getImage().size();
            emit loginOK(userMessage);
            break;
        }
        case MessageType::S_LOGIN_KO:{
            emit loginKO();
            break;
        }
        case MessageType::S_INPUT_KO:{
            //Old psw not correct
            emit errorOldPwd();
            break;
        }
        case MessageType::S_NOT_LOGGED:{
            emit notLogged();
            break;
        }
        case MessageType::S_UPD_KO:{
            emit updateKO();
            break;
        }
        case MessageType::S_UPD_OK:{
            emit updateOK(userData);
            break;
        }
    }


}

void SocketClient::registrationMessage(User userRegistration){

    userData=userRegistration;
    qInfo() << "Registratione";
    Header haederReg(MessageType::C_REGISTER) ;
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_12);
    qInfo() << "Send packet registration";
    clientStream << haederReg << userRegistration;
}

void SocketClient::loginMessage(User userLogin)
{
    qInfo() << "Login";
    Header haederReg(MessageType::C_LOGIN) ;
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_12);
    qInfo() << "Send packet login";
    clientStream << haederReg << userLogin;
}

void SocketClient::updateImage(User user)
{
    userData = user;
    qInfo() << "Update Image";
    Header haederReg(MessageType::C_UPD_IMG) ;
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_12);
    qInfo() << "Send packet update image";
    clientStream << haederReg << user;
}

void SocketClient::updateName(User user)
{
    userData = user;
    qInfo()<<"Update name";
    Header haederReg(MessageType::C_UPD_NAME) ;
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_12);
    qInfo() << "Send packet update name";
    clientStream << haederReg << user;
}

void SocketClient::updateSurname(User user)
{
    userData = user;
    qInfo()<<"Update surname";
    Header haederReg(MessageType::C_UPD_SURN) ;
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_12);
    qInfo() << "Send packet update surname";
    clientStream << haederReg << user;
}

void SocketClient::updatePassword(User user)
{
    userData = user;
    qInfo()<<"Update password";
    Header haederReg(MessageType::C_UPD_PASS) ;
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_12);
    qInfo() << "Send packet update password";
    clientStream << haederReg << user;
}


