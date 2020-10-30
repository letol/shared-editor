#ifndef ONLINEUSERSDIALOG_H
#define ONLINEUSERSDIALOG_H

#include <QDialog>
#include <QMap>
#include <notepad.h>

namespace Ui {
class OnlineUsersDialog;
}

class OnlineUsersDialog : public QDialog
{
    Q_OBJECT

public:

    explicit OnlineUsersDialog(QList<RemoteUser> onlineUsers, QWidget *parent = nullptr);
    ~OnlineUsersDialog();



private:
    Ui::OnlineUsersDialog *ui;
    QList<RemoteUser> onlineUsers;


private slots:
    void userLogged(const User& user);


};

#endif // ONLINEUSERSDIALOG_H
