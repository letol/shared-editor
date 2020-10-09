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

// connected to server
// esempio di come mandare un pacchetto.
void SocketClient::connected()
{
    /*qDebug() << "Connected!";
    Header header(MessageType::C_LOGIN);
    // Message messageLogin(QString("pippo"), QString("plutio"));

   // socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n");
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_12);
    qDebug() << "Send packet";
    clientStream << header;*/
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

    socketStream >> header;

    switch(header.getType())
    {

        case MessageType::S_REGISTER_OK:{
         emit registrationOK();
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
            emit loginOK();
            break;
        }
        case MessageType::S_LOGIN_KO:{
            emit loginKO();
            break;
        }
    }


}

void SocketClient::registrationMessage(User userRegistration){

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

//Password#01
