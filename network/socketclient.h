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

public slots:
    void connected();
    void disconnected();
    void bytesWritten (qint64 bytes);
    void readyRead();
    void registrationMessage(User userRegistration);

private:
    QTcpSocket *socket;
};

#endif // SOCKETCLIENT_H
