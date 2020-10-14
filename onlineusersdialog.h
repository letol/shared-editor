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

     explicit OnlineUsersDialog(QWidget *parent = nullptr);
    explicit OnlineUsersDialog(QList<RemoteUser> &onlineUsers, QWidget *parent = nullptr);
    ~OnlineUsersDialog();



private:
    Ui::OnlineUsersDialog *ui;
    QList<RemoteUser> onlineUsers;


private slots:


};

#endif // ONLINEUSERSDIALOG_H
