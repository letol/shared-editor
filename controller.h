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
    void enableEditingMessages();

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
    void remoteCursorPositionChanged(QUuid siteId, int newPos);
    void pushOnlineUsers(QMap<QUuid, User> onlineUsers);



public slots:
    void open();
    void moveOnlineUsers(QMap<QUuid, User> onlineUsers);
    void moveUserDisconnected(QUuid uuid);
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
    void newDocument(const QVector<Symbol>& symbols, const QString& name);
    void newDocumentOK(const DocumentMessage& newDocReply);
    void newDocumentKO();
    void fileClosed();
    void documentListOK(QVector<DocumentMessage>& docList);
    void documentListKO();
    void openDocument(const QUrl uri);
    void openDocumentOK(const DocumentMessage& docReply);
    void openDocumentKO();
    void sendCursorPosition(int pos);
    void receiveCursorPosition(const CursorPositionMessage& curPosMsg);

private:
    QUuid siteId;
    Notepad* notepad;
    SocketClient socket;
    LoginDialog *logindialog;
    RegistrationDialog *regDialog;
    OpenFileDialog *openfile;
    UpdateFormDialog *updateForm;
    ConfirmPassword* confirmpwd;
    User currentUser;
    DocumentMessage currentDocument;
    bool changePwd=false;
    bool userIsLogged=false;

};

#endif // CONTROLLER_H
