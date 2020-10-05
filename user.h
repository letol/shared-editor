#ifndef USER_H
#define USER_H

#include <QObject>

class User
{

private:
    QString name;
    QString surname;
    QString nickname;
    QString email;
    QString password;
    QByteArray *image;
public:
    User(QString name, QString surname, QString nickname, QString email, QString password,QByteArray *image);
    QString getEmail();
    QString getNickname();
    QString getPassword();
    QString getName();
    QString getSurname();
    QByteArray*  getImage();

};

#endif // USER_H
