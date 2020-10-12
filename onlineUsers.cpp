#include "onlineUsers.h"

onlineUsers::onlineUsers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::onlineUsers)
{
    ui->setupUi(this);
}

onlineUsers::~onlineUsers()
{
    delete ui;
}
