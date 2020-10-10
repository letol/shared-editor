#ifndef ONLINEUSERS_H
#define ONLINEUSERS_H

#include <QDialog>
#include <notepad.h>

namespace Ui {
class onlineUsers;
}

class onlineUsers: public QDialog
{
    Q_OBJECT

 public:
    explicit onlineUsers(QWidget *parent = nullptr);
    ~onlineUsers();

private:
      Ui::onlineUsers *ui;


};

#endif // ONLINEUSERS_H
