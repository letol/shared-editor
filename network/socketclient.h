#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "header.h"
#include "messageType.h"
#include "user.h"

class SocketClient : public QObject
{
    Q_OBJECT
public:
    explicit SocketClient(QObject *parent = 0);
    void setSocket();

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

public slots:
    void disconnected();
    void bytesWritten (qint64 bytes);
    void readyRead();
    void registrationMessage(User userRegistration);
    void loginMessage(User userLogin);
    void updateImage(User user);
    void updateName(User user);
    void updateSurname(User user);
    void updatePassword(User user);

private:
    QTcpSocket *socket;
    User userData;
};

#endif // SOCKETCLIENT_H
