#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "notepad.h"
#include "registrationdialog.h"
#include "socketclient.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_clicked();
    void receveRegistrationData(const User& user);

private:
    Ui::LoginDialog *ui;
    Notepad *notepad;
    RegistrationDialog *registration;
    SocketClient socket;

};

#endif // LOGINDIALOG_H
