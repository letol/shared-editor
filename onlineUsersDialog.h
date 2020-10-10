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
    ~OnlineUsersDialog();

    void getCountofUsers(QMap<int,RemoteUser> OnlineUsers);

private:
    Ui::OnlineUsersDialog *ui;

};

#endif // ONLINEUSERSDIALOG_H
