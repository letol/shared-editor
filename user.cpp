#include "user.h"

User::User(QString name, QString surname, QString nickname, QString email, QString password,QByteArray *image)
{
    this->name=name;
    this->surname=surname;
    this->nickname=nickname;
    this->email=email;
    this->password=password;
    this->image=image;

}

QString User::getEmail(){
    return this->email;
}
QString User::getName(){
    return this->name;
}
QString User::getNickname(){
    return this->nickname;
}
QString User::getPassword(){
    return this->password;
}
QString User::getSurname(){
    return surname;
}
QByteArray* User::getImage(){
    return this->image;
}
