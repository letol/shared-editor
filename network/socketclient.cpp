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
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
                    this, SLOT(error(QAbstractSocket::SocketError)) , Qt::DirectConnection);

    qDebug() << "Connecting...";

    // Server IP -> We will insert it in command line before launch the program
    socket->connectToHost("127.0.0.1",1800);

    if(!socket->waitForConnected(5000))
    {
       qDebug() << "Error: " <<  socket->errorString();
       //emit errorServer();
    }
}

void SocketClient::connected()
{
    if(!socket->waitForConnected(5000)){
        qInfo()<<"error";

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
    // Start to read the message
    socketStream.startTransaction();


    socketStream >> header;
    switch(header.getType())
    {

        case MessageType::S_REGISTER_OK:{
            if (!socketStream.commitTransaction())
                return;

             emit registrationOK(userData);
             break;
        }
        case MessageType::S_REGISTER_KO:{
            if (!socketStream.commitTransaction())
                return;
            emit registrationKO();
            break;
        }
        case MessageType::S_ERROR_DB:{
            if (!socketStream.commitTransaction())
                return;
            emit errorDB();
            break;
        }
        case MessageType::S_LOGIN_OK:{

            socketStream>>userMessage;
                    //User("taba95","Raluca","Tabacaru","t.rg@gmail.com","Password#01","");
            if (!socketStream.commitTransaction())
                return;
            qDebug()<< "Received: " ;
            qDebug()<< "image size: " << userMessage.getImage().size();
            qDebug()<< "name: " << userMessage.getName();
            qDebug()<< "surname: " << userMessage.getSurname();
            qDebug()<< "email: " << userMessage.getEmail();
            qDebug()<< "nickname: " << userMessage.getNickname();
            qDebug()<< "password: " << userMessage.getPassword();
            emit loginOK(userMessage);
            break;
        }
        case MessageType::S_LOGIN_KO:{
            if (!socketStream.commitTransaction())
                return;
            emit loginKO();
            break;
        }
        case MessageType::S_INPUT_KO:{
            //Old psw not correct
            if (!socketStream.commitTransaction())
                return;
            qInfo()<<"Error pwd";
            emit errorOldPwd();
            break;
        }
        case MessageType::S_NOT_LOGGED:{
            if (!socketStream.commitTransaction())
                return;
            qInfo()<<"Not logged";
            emit notLogged();
            break;
        }
        case MessageType::S_UPD_KO:{
            if (!socketStream.commitTransaction())
                return;
            qInfo()<<"upd ko";
            emit updateKO();

            break;
        }

        case MessageType::S_UPD_OK:{
            if (!socketStream.commitTransaction())
                return;
            qInfo()<<"upd ok";
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

void SocketClient::error(QAbstractSocket::SocketError socketError)
{
       emit errorServer();
}


