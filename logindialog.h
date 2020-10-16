#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "registrationdialog.h"
#include "user.h"



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
    void loginData(const User& user);
    void registrationData(const User& user);


private slots:
    void on_pushButton_login_clicked();
    void on_pushButton_clicked();
    void receveRegistrationData(const User& user);
    void regOK();
    void regKO(const QString& str);

    void logKO(const QString& str);
    void showDialog();


private:
    Ui::LoginDialog *ui;
    RegistrationDialog *registration;


};

#endif // LOGINDIALOG_H
