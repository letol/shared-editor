#include "onlineusersdialog.h"
#include "remoteuser.h"
#include "ui_onlineusersdialog.h"
#include "notepad.h"
#include <QGridLayout>
#include <QPainterPath>
#include <QPainter>
#include <QHBoxLayout>
#include <QLayout>
#include <QListWidget>
#include <QListWidgetItem>

OnlineUsersDialog::OnlineUsersDialog(QList<RemoteUser> onlineUsers, QWidget *parent):
    QDialog(parent),
    ui(new Ui::OnlineUsersDialog),
    onlineUsers(onlineUsers)
{
    ui->setupUi(this);

    this->setWindowTitle("Online Users");

    QListWidget* listWidget = new QListWidget(this);
    listWidget->setStyleSheet("background-color: transparent;");

    for (int i=0; i<onlineUsers.count(); i++) {

        QImage image;

        image.loadFromData(onlineUsers[i].getUserInfo().getImage());
        QPixmap qImage = QPixmap::fromImage(image);
        QPixmap pixmap(50,50);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        QPainterPath path;
        path.addEllipse(0, 0, 50, 50);
        painter.setClipPath(path);
        painter.drawPixmap(0, 0, 50, 50, qImage);

        QString userString = onlineUsers[i].getUserInfo().getName() + " " + onlineUsers[i].getUserInfo().getSurname();

        listWidget->addItem(new QListWidgetItem(QIcon(pixmap), userString));
    }

/*
//TO TRY


QImage image;
image.load(":/images/profile.png");
QPixmap qImage = QPixmap::fromImage(image);
QPixmap pixmap(50,50);
pixmap.fill(Qt::transparent);
QPainter painter(&pixmap);
painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
QPainterPath path;
path.addEllipse(0, 0, 50, 50);
painter.setClipPath(path);
painter.drawPixmap(0, 0, 50, 50, qImage);
 listWidget->addItem(new QListWidgetItem(QIcon(pixmap
                                              ),"some text"));
 listWidget->addItem(new QListWidgetItem(QIcon(pixmap
                                              ),"ciao"));
*/
}

OnlineUsersDialog::~OnlineUsersDialog()
{
    delete ui;
}






