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
    QImage *image;
public:
    User(QString name, QString surname, QString nickname, QString email, QString password,QImage *image);
    QString getEmail();
    QString getNickname();
    QString getPassword();
    QString getName();
    QString getSurname();
    QImage*  getImage();

};

#endif // USER_H
