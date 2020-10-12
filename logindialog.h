#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "notepad.h"
#include "registrationdialog.h"
#include "socketclient.h"
#include "openfiledialog.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

signals:
    void messageRegDialog(const QString& str);
    void closeRegDialog();


private slots:
    void on_pushButton_login_clicked();
    void on_pushButton_clicked();
    void receveRegistrationData(const User& user);
    void regOK();
    void regKO();
    void logOK();
    void logKO();
    void errorDB();
    void showDialog();


private:
    Ui::LoginDialog *ui;
    OpenFileDialog *openfile;
    //Notepad *notepad;
    RegistrationDialog *registration;
    SocketClient socket;

};

#endif // LOGINDIALOG_H
