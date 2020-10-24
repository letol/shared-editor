#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
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
    void loginData(const User& user);
    void clickSignIn();



private slots:
    void on_pushButton_login_clicked();
    void on_pushButton_clicked();
    void logKO(const QString& str);
    void on_lineEdit_username_textChanged();
    void on_lineEdit_password_textChanged();
    void clean();

private:
    Ui::LoginDialog *ui;


};

#endif // LOGINDIALOG_H
