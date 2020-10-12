#include "onlineusersdialog.h"
#include "remoteuser.h"
#include "ui_onlineusersdialog.h"

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

void OnlineUsersDialog::getCountofUsers(QMap<int,RemoteUser> OnlineUsers){

}
