#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "header.h"
#include "messageType.h"
#include "user.h"
#include "messages/documentmessage.h"
#include "messages/editingmessage.h"
#include "messages/openmessage.h"
#include "messages/cursorpositionmessage.h"

class SocketClient : public QObject
{
    Q_OBJECT
public:
    explicit SocketClient(QObject *parent = 0);
    void setSocket();
    void closeSocket();

signals:
    void registrationOK(const User& user);
    void registrationKO();
    void loginOK(const User& user);
    void loginKO();
    void errorDB();
    void notLogged();
    void updateOK(const User& user);
    void updateKO();
    void errorOldPwd();
    void errorServer();
    void newDocumentKO();
    void newDocumentOK(const DocumentMessage& newDocReply);
    void remoteEditDocument(const EditingMessage& editMsg);
    void documentListKO();
    void documentListOK(QVector<DocumentMessage>& docList);
    void openDocumentOK(const DocumentMessage& docReply);
    void openDocumentKO();
    void remoteCursorPosition(const CursorPositionMessage& curPosMsg);
    void errorUri();
    void uriOK();

public slots:
    void connected();
    void disconnected();
    void bytesWritten (qint64 bytes);
    void readyRead();
    void registrationMessage(User userRegistration);
    void loginMessage(User userLogin);
    void updateImage(User user);
    void updateName(User user);
    void updateSurname(User user);
    void updatePassword(User user);
    void newDocument(const DocumentMessage& newDocMsg);
    void error();
    void localEditDocument(const EditingMessage& editMsg);
    void askForDocumentList(const QString userEmail);
    void openDocument(const OpenMessage openMsg);
    void localCursorPosition(const CursorPositionMessage curPosMsg);


private:
    QTcpSocket *socket;
    User userData;
};

#endif // SOCKETCLIENT_H
