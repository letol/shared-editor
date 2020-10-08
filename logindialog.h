#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <notepad.h>
#include <registrationdialog.h>

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

private:
    Ui::LoginDialog *ui;
    Notepad *notepad;
    RegistrationDialog *registration;

};

#endif // LOGINDIALOG_H
