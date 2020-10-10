#include "onlineUsersDialog.h"
#include "remoteuser.h"
#include "ui_onlineUsersDialog.h"

OnlineUsersDialog::OnlineUsersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OnlineUsersDialog)
{
    ui->setupUi(this);
}

OnlineUsersDialog::~OnlineUsersDialog()
{
    delete ui;
}

OnlineUsersDialog::getCountofUsers(QMap<int,RemoteUser> OnlineUsers){

}
