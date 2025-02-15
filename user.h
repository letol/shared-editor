#ifndef USER_H
#define USER_H
#include "serialization.h"
#include <QCryptographicHash>
#include <QtCore>

#include <QObject>

class User : public Serialization
{

private:
    QString name;
    QString surname;
    QString nickname;
    QString email;
    QString password;
    QByteArray image;
public:
    User(QString nickname, QString name, QString surname,  QString email, QString password,QByteArray image);
    User(QString username, QString password);
    User() = default;

    QString getEmail();
    QString getNickname();
    QString getPassword();
    QString getName();
    QString getSurname();
    QByteArray  getImage();
    void setImage(QByteArray arr);

    QDataStream &serialize(QDataStream &stream) const override;
    QDataStream &unserialize(QDataStream &stream) override;
};
Q_DECLARE_METATYPE(User)

#endif // USER_H
