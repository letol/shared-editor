#include "controller.h"
#include <QMessageBox>

Controller::Controller(QWidget *parent) :
    QWidget(parent)
{
    siteId = QUuid::createUuid();
    socket.setSocket();

    notepad = new Notepad(siteId);
    logindialog = new LoginDialog();
    regDialog = new RegistrationDialog();
    openfile = new OpenFileDialog();
    updateForm = new UpdateFormDialog();

    confirmpwd = new ConfirmPassword();
    //socket connection
    connect(&socket,SIGNAL(errorServer()),this,SLOT(errorConnection()));
    connect(&socket,&SocketClient::registrationOK,this,&Controller::regOK);
    connect(&socket,&SocketClient::registrationKO,this,&Controller::regKO);
    connect(&socket,&SocketClient::loginOK,this,&Controller::logOK);
    connect(&socket,&SocketClient::loginKO,this,&Controller::logKO);
    connect(&socket,&SocketClient::errorDB,this,&Controller::errorDB);
    connect(&socket,&SocketClient::errorOldPwd,this,&Controller::errorPwd);
    connect(&socket,&SocketClient::notLogged,this,&Controller::notLogged);
    connect(&socket,&SocketClient::updateOK,this,&Controller::updateOK);
    connect(&socket,&SocketClient::updateKO,this,&Controller::updeteKO);
    connect(&socket,&SocketClient::newDocumentOK,this,&Controller::newDocumentOK);
    connect(&socket,&SocketClient::newDocumentKO,this,&Controller::newDocumentKO);
    connect(&socket,&SocketClient::documentListOK,this,&Controller::documentListOK);
    connect(&socket,&SocketClient::documentListKO,this,&Controller::documentListKO);
    connect(&socket,&SocketClient::openDocumentOK,this,&Controller::openDocumentOK);
    connect(&socket,&SocketClient::openDocumentKO,this,&Controller::openDocumentKO);
    connect(&socket,&SocketClient::addOnlineUser,this,&Controller::moveOnlineUsers);
    connect(&socket,&SocketClient::removeOnlineUser,this,&Controller::moveUserDisconnected);

    connect(logindialog,SIGNAL(loginData(User)),this,SLOT(loginData(User)));
    connect(this,SIGNAL(errorLogin(QString)),logindialog,SLOT(logKO(QString)));
    connect(logindialog,SIGNAL(clickSignIn()),this,SLOT(openReg()));
    connect(this,SIGNAL(loginDialogClear()),logindialog,SLOT(clean()));

    connect(regDialog,SIGNAL(registratationData(User)),this,SLOT(regData(User)));
    connect(this,SIGNAL(errorReg(QString)),regDialog,SLOT(errorHeadling(QString)));
    connect(regDialog,SIGNAL(openLogin()),this,SLOT(openLogin()));

    connect(notepad,&Notepad::showUpdateForm, this, &Controller::showUpdateForm);
    connect(this,&Controller::updateButton,notepad,&Notepad::updateButtonIcon);
    connect(openfile,&OpenFileDialog::openFile,this, &Controller::openDocument);
    connect(openfile,&OpenFileDialog::openNewFile,notepad,&Notepad::openNewDocument);
    connect(notepad, &Notepad::newDocument, this, &Controller::newDocument);
    connect(notepad, &Notepad::fileClosed, this, &Controller::fileClosed);
    connect(notepad,&Notepad::logout,this,&Controller::logout);
    connect(this,&Controller::pushOnlineUsers,notepad,&Notepad::getOnlineUsers);
    connect(this,SIGNAL(userLogged(User)),updateForm,SLOT(userLogged(User)));
    connect(this,SIGNAL(userIsChanged(User)),updateForm,SLOT(updateOK(User)));
    connect(this,SIGNAL(udpKO(QString)),updateForm,SLOT(updateKO(QString)));

    connect(updateForm,SIGNAL(nameChange(QString)),this,SLOT(nameChanged(QString)));
    connect(updateForm,SIGNAL(surnameChange(QString)),this,SLOT(surnameChanged(QString)));
    connect(updateForm,SIGNAL(imageChange(QByteArray)),this,SLOT(imageChanged(QByteArray)));
    connect(updateForm,SIGNAL(showCP()),this,SLOT(openCP()));
    connect(updateForm,&UpdateFormDialog::logout,this,&Controller::logout);

    connect(confirmpwd,SIGNAL(passwordData(QString,QString)),this,SLOT(pwdChanged(QString,QString)));
    connect(this,&Controller::pwdKO,confirmpwd,&ConfirmPassword::errorPwd);
    connect(this,SIGNAL(pwdOK()),confirmpwd,SLOT(updOK()));

}

Controller::~Controller()
{
}

void Controller::enableEditingMessages()
{
    connect(notepad->getSharedEditor(),&SharedEditor::localChange,&socket,&SocketClient::localEditDocument);
    connect(&socket,&SocketClient::remoteEditDocument,notepad->getSharedEditor(),&SharedEditor::process);
    connect(notepad,&Notepad::newCursorPosition,this,&Controller::sendCursorPosition);
    connect(&socket,&SocketClient::remoteCursorPosition,this,&Controller::receiveCursorPosition);
    connect(this,&Controller::remoteCursorPositionChanged,notepad,&Notepad::remoteCursorPositionChanged);
}

void Controller::open()
{
   if(!userIsLogged){
        logindialog->show();
    }else{
        socket.askForDocumentList(currentUser.getEmail());
        openfile->show();
    }




}

void Controller::moveOnlineUsers(QMap<QUuid, User> onlineUsers)
{
   onlineUsers.remove(siteId);
   emit pushOnlineUsers(onlineUsers);
}

void Controller::moveUserDisconnected(QUuid uuid)
{
    notepad->removeRemoteUser(uuid);


}

void Controller::errorConnection()
{

    QMessageBox::critical(this,"Error","Something went wrong!Please try again later.");
    notepad->close();
    openfile->close();
    logindialog->close();
    regDialog->close();
    updateForm->close();
    confirmpwd->close();
    this->close();
}

void Controller::showUpdateForm()
{
    updateForm->show();
}

void Controller::regOK(const User& user)
{
    currentUser = std::move(user);
    //to updateForm
    emit userLogged(currentUser);
    userIsLogged=true;

    QImage imagex;
    imagex.loadFromData(currentUser.getImage());
    QString str =currentUser.getName()+" "+currentUser.getSurname();
    qInfo()<<currentUser.getImage().size();
    qInfo()<<imagex.size();
    //to updateButton in notepad
    emit updateButton(str,imagex);


    regDialog->close();
    socket.askForDocumentList(currentUser.getEmail());
    openfile->show();
}

void Controller::regKO()
{
    //to registration dialog
   emit errorReg("Email or nickname are already used");

}

void Controller::logOK(const User& user)
{

    currentUser=std::move(user);
    notepad->getSharedEditor()->setUserEmail(currentUser.getEmail());
    //to update dialog
    emit userLogged(currentUser);
    userIsLogged=true;
    QImage imagex;
    qInfo()<<currentUser.getImage().size();
    imagex.loadFromData(currentUser.getImage());

    emit updateButton(currentUser.getName()+" "+currentUser.getSurname(),imagex);
    emit loginDialogClear();
    logindialog->close();
    socket.askForDocumentList(currentUser.getEmail());
    openfile->show();
}

void Controller::logKO()
{
  //to login dialog
  emit errorLogin("Username and password are not valid");
}

void Controller::errorDB()
{
    QMessageBox::warning(this,"Error", "Something went wrong!Please try again later.");
    notepad->close();
    openfile->close();
    logindialog->close();
    regDialog->close();
    updateForm->close();
    confirmpwd->close();
    this->close();
}

void Controller::notLogged()
{
    QMessageBox::warning(this,"Error", "Plese login");
    notepad->close();
    openfile->close();
    regDialog->close();
    updateForm->close();
    confirmpwd->close();
    logindialog->show();
}

void Controller::updateOK(const User& user)
{
   User userChanged= std::move(user);
   currentUser = User(currentUser.getNickname(),userChanged.getName(),userChanged.getSurname(),currentUser.getEmail(),userChanged.getPassword(),userChanged.getImage());
   QImage imagex;
   imagex.loadFromData(currentUser.getImage());
   if(changePwd){
       emit pwdOK();
       changePwd=false;
   }
   emit updateButton(currentUser.getName()+" "+currentUser.getSurname(),imagex);
   //to updateFormDialog
   emit userIsChanged(currentUser);
}

void Controller::updeteKO()
{
    emit udpKO("Something went wrong. Try later.");
}

void Controller::errorPwd()
{
    emit pwdKO("Password not valid.");
    changePwd=false;
}

void Controller::pwdChanged(const QString &pwd, const QString &pwdNew)
{
    User userChange = User(currentUser.getNickname(),currentUser.getName(),currentUser.getSurname(),pwd,pwdNew,currentUser.getImage());
    changePwd=true;
    socket.updatePassword(userChange);
}

void Controller::nameChanged(const QString &name)
{
    User userChange = User(currentUser.getNickname(),name,currentUser.getSurname(),currentUser.getEmail(),currentUser.getPassword(),currentUser.getImage());

    socket.updateName(userChange);
}

void Controller::surnameChanged(const QString &surname)
{
    User userChange = User(currentUser.getNickname(),currentUser.getName(),surname,currentUser.getEmail(),currentUser.getPassword(),currentUser.getImage());
    socket.updateSurname(userChange);
}

void Controller::imageChanged(const QByteArray &image)
{
    User userChange = User(currentUser.getNickname(),currentUser.getName(),currentUser.getSurname(),currentUser.getEmail(),currentUser.getPassword(),image);
    socket.updateImage(userChange);
}

void Controller::loginData(const User &user)
{
    socket.loginMessage(user);
}

void Controller::regData(const User &user)
{

    socket.registrationMessage(user);

}

void Controller::openReg()
{
    regDialog->show();
}

void Controller::openLogin()
{
    logindialog->show();

}

void Controller::openCP()
{
    confirmpwd->show();
}

void Controller::logout()
{
    userIsLogged=false;
    currentUser= User();
    socket.closeSocket();
    socket.setSocket();
    notepad->close();
    updateForm->close();
    confirmpwd->close();
    emit loginDialogClear();
    logindialog->show();

}


void Controller::newDocument(const QVector<Symbol>& symbols, const QString& name)
{
    DocumentMessage newDocMsg{currentUser.getEmail(), name, symbols};
    socket.newDocument(newDocMsg);
}

void Controller::newDocumentOK(const DocumentMessage& newDocReply)
{
    currentDocument = std::move(newDocReply);
    enableEditingMessages();
}

void Controller::newDocumentKO()
{
    QMessageBox::warning(this,"Error", "Error creating new file.");
    openfile->show();
}

void Controller::fileClosed()
{
    notepad->close();
    updateForm->close();
    confirmpwd->close();
    currentDocument = DocumentMessage();
    socket.askForDocumentList(currentUser.getEmail());
    openfile->clean();
    openfile->show();
}

void Controller::documentListOK(QVector<DocumentMessage>& docList)
{
    openfile->setFileList(docList);

}

void Controller::documentListKO()
{
    QMessageBox::warning(this,"Error", "Impossible to load document list.");
}

void Controller::openDocument(const QUrl uri)
{
    qDebug() << "Opening document" << uri.toString();
    OpenMessage openMsg(siteId, uri);
    socket.openDocument(openMsg);
}

void Controller::openDocumentOK(const DocumentMessage& docReply)
{
    currentDocument = std::move(docReply);
    enableEditingMessages();
    notepad->openExistingDocument(currentDocument.getSymbols(), currentDocument.getName(),currentDocument.getDocumentId());
}

void Controller::openDocumentKO()
{
    QMessageBox::warning(this,"Error", "Impossible to load document.");
    openfile->show();
}

void Controller::sendCursorPosition(int pos)
{
    CursorPositionMessage curPosMsg(pos, siteId);
    socket.localCursorPosition(curPosMsg);
}

void Controller::receiveCursorPosition(const CursorPositionMessage& curPosMsg)
{
    CursorPositionMessage m = std::move(curPosMsg);
    emit remoteCursorPositionChanged(m.getSiteId(), m.getPos());
}
