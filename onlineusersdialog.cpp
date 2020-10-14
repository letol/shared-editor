#include "onlineusersdialog.h"
#include "remoteuser.h"
#include "ui_onlineusersdialog.h"
#include "notepad.h"


OnlineUsersDialog::OnlineUsersDialog( QList<RemoteUser> &onlineUsers, QWidget *parent):
    QDialog(parent),
    ui(new Ui::OnlineUsersDialog),
    onlineUsers(onlineUsers)
{
    ui->setupUi(this);


    for (int i=0; i<onlineUsers.count(); i++) {
        QLabel label;
        QPixmap image;

        //convert QBitemap into QPixmap
        image.loadFromData(onlineUsers[i].getUserInfo().getImage());
        label.setPixmap(image);
        label.setText("<font color='onlineUsers[i].getColor()>text</font>");
    }
}

OnlineUsersDialog::~OnlineUsersDialog()
{
    delete ui;
}






