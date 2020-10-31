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
    qDebug() << "writed "<<bytes;
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
    retry:
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

        case MessageType::S_NEW_KO: {
            qDebug() << "Received: S_NEW_KO";
            if (!socketStream.commitTransaction())
                return;
            emit newDocumentKO();
            break;
        }

        case MessageType::S_NEW_OK: {
            qDebug() << "Received: S_NEW_OK";
            DocumentMessage docMsg;
            socketStream >> docMsg;
            if (!socketStream.commitTransaction())
                return;
            emit newDocumentOK(docMsg);
            break;
        }

        case MessageType::B_EDIT: {
            qDebug() << "Received: B_EDIT";
            EditingMessage editMsg;
            socketStream >> editMsg;
            if (!socketStream.commitTransaction())
                return;
            emit remoteEditDocument(editMsg);
            break;
        }

        case MessageType::S_DOCLS_KO: {
            qDebug() << "Received: S_DOCLS_KO";
            if (!socketStream.commitTransaction())
                return;
            emit documentListKO();
            break;
        }

        case MessageType::S_DOCLS_OK: {
            qDebug() << "Received: S_DOCLS_OK";
            int size;
            socketStream >> size;
            qDebug() << "List size:" << size;

            QVector<DocumentMessage> docList;
            for (int i=0; i<size; i++) {
                DocumentMessage d;
                socketStream >> d;
                docList.append(d);
                qDebug() << "Received document:" << d.getDocumentId();
            }

            if (!socketStream.commitTransaction())
                return;

            emit documentListOK(docList);
            break;
        }

        case MessageType::S_OPEN_KO: {
            qDebug() << "Received: S_OPEN_KO";
            if (!socketStream.commitTransaction())
                return;
            emit openDocumentKO();
            break;
        }

        case MessageType::S_OPEN_OK: {
            qDebug() << "Received: S_OPEN_OK";
            DocumentMessage docMsg;
            socketStream >> docMsg;
            if (!socketStream.commitTransaction())
                return;
            emit openDocumentOK(docMsg);
            break;
        }

        case MessageType::B_CURSOR_POS: {
            qDebug() << "Received: B_CURSOR_POS";
            CursorPositionMessage curPosMsg;
            socketStream >> curPosMsg;
            if (!socketStream.commitTransaction())
                return;
            emit remoteCursorPosition(curPosMsg);
            break;
        }

        case MessageType::S_ONL_USRS: {
            QMap<QUuid, User> onlineUsers;
            socketStream >> onlineUsers;
            if (!socketStream.commitTransaction())
                return;
            qDebug() << "Received: list of online users"<<onlineUsers.values().length();

            //qDebug() << "Received: list of online users"<<onlineUsers.values();
            emit addOnlineUser(onlineUsers);
            break;
        }

        case MessageType::S_RMV_USR: {
            qDebug() << "Received: list of online users";
            QUuid uuid;
            socketStream >> uuid;
            if (!socketStream.commitTransaction())
                return;
            emit removeOnlineUser(uuid);
            break;
        }
        case MessageType::S_DOC_DLT_OK:{
            if (!socketStream.commitTransaction())
                return;
            emit deleteOK();
            break;
        }
        case MessageType::S_DOC_DLT_KO:{
            if (!socketStream.commitTransaction())
                return;
            emit deleteKO();
            break;
        }
      
        default:{
            qDebug() << "Unknown MessageType: wait for more data";
            if (!socketStream.commitTransaction())
                return;     // wait for more data
        }
    }

    if (socket->bytesAvailable() > 0)
        goto retry;
}

void SocketClient::registrationMessage(User userRegistration){

    userData = userRegistration;
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

void SocketClient::newDocument(const DocumentMessage& newDocMsg) {
    Header headerReg(MessageType::C_NEW) ;
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_12);
    clientStream << headerReg << newDocMsg;
    qDebug() << "Sent: C_NEW";
}

void SocketClient::error()
{
       emit errorServer();
}

void SocketClient::localEditDocument(const EditingMessage& editMsg) {
    Header headerReg(MessageType::B_EDIT) ;
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_12);
    clientStream << headerReg << editMsg;
    qDebug() << "Sent: B_EDIT";
    qDebug() << "Sent" << editMsg.getOperation() << editMsg.getSymbol().getValue();
}

void SocketClient::askForDocumentList(const QString userEmail) {
    Header headerReg(MessageType::C_DOCLS) ;
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_12);
    clientStream << headerReg << userEmail;
    qDebug() << "Sent: C_DOCLS";
}

void SocketClient::openDocument(const OpenMessage openMsg) {
    Header headerReg(MessageType::C_OPEN) ;
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_12);
    clientStream << headerReg << openMsg;
    qDebug() << "Sent: C_OPEN" << openMsg.getUri();
}

void SocketClient::localCursorPosition(const CursorPositionMessage curPosMsg) {
    Header headerReg(MessageType::B_CURSOR_POS) ;
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_12);
    clientStream << headerReg << curPosMsg;
    qDebug() << "Sent: B_CURSOR_POS";
}

void SocketClient::deleteMessage(DocumentMessage docMessage)
{
    Header headerReg(MessageType::C_DOC_DLT) ;
    QDataStream clientStream(socket);
    clientStream.setVersion(QDataStream::Qt_5_12);
    clientStream << headerReg << docMessage;
    qDebug() << "Sent: C_DOC_DLT";
}
