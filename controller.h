#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
#include "notepad.h"
#include "logindialog.h"
#include "registrationdialog.h"
#include "openfiledialog.h"
#include "updateformdialog.h"
#include "confirmpassword.h"
#include "socketclient.h"
#include "onlineusersdialog.h"


class Controller : public QWidget
{
    Q_OBJECT

public:
    explicit Controller(QWidget *parent = nullptr);
    ~Controller();
signals:
    void updateButton(const QString& nameSurname,const QImage& image);
    void errorLogin(const QString& str);
    void errorReg(const QString& str);
    void udpKO(const QString& str);
    void pwdKO(const QString& str);
    void userIsChanged(const User& user);
    void userLogged(const User& user);
    void pwdOK();
    void loginDialogClear();


public slots:
    void open();
private slots:
    void showUpdateForm();
    void regOK(const User& user);
    void regKO();
    void logOK(const User& user);
    void logKO();
    void errorDB();
    void notLogged();
    void updateOK(const User& user);
    void updeteKO();
    void errorPwd();
    void pwdChanged(const QString& pwd,const QString& pwdNew);
    void nameChanged(const QString& name);
    void surnameChanged(const QString& surname);
    void imageChanged(const QByteArray& image);
    void errorConnection();
    void loginData(const User& user);
    void regData(const User& user);
    void openReg();
    void openLogin();
    void openCP();
    void logout();
private:
    Notepad* notepad;
    SocketClient socket;
    LoginDialog *logindialog;
    RegistrationDialog *regDialog;
    OpenFileDialog *openfile;
    UpdateFormDialog *updateForm;
    ConfirmPassword* confirmpwd;
    User currentUser;
    bool changePwd=false;
    bool userIsLogged=false;
    OnlineUsersDialog* onlineUD;
};

#endif // CONTROLLER_H
