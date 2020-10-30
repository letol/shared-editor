#include "controller.h"
#include <QMessageBox>

Controller::Controller(QWidget *parent) :
    QWidget(parent)
{

    socket.setSocket();
    notepad = new Notepad();
    logindialog = new LoginDialog();
    regDialog = new RegistrationDialog();
    openfile = new OpenFileDialog();
    updateForm = new UpdateFormDialog();
    confirmpwd= new ConfirmPassword();
    onlineUD = new OnlineUsersDialog(notepad->remoteUsers.values());

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



    connect(logindialog,SIGNAL(loginData(User)),this,SLOT(loginData(User)));
    connect(this,SIGNAL(errorLogin(QString)),logindialog,SLOT(logKO(QString)));
    connect(logindialog,SIGNAL(clickSignIn()),this,SLOT(openReg()));
    connect(this,SIGNAL(loginDialogClear()),logindialog,SLOT(clean()));

    connect(regDialog,SIGNAL(registratationData(User)),this,SLOT(regData(User)));
    connect(this,SIGNAL(errorReg(QString)),regDialog,SLOT(errorHeadling(QString)));
    connect(regDialog,SIGNAL(openLogin()),this,SLOT(openLogin()));

    connect(notepad,&Notepad::showUpdateForm, this, &Controller::showUpdateForm);
    connect(this,&Controller::updateButton,notepad,&Notepad::updateButtonIcon);
    connect(openfile,SIGNAL(openFile(QString)),notepad,SLOT(open(QString)));
    connect(openfile,SIGNAL(openNewFile()),notepad,SLOT(newDocument()));

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
    delete this;
}

void Controller::open()
{
    if(!userIsLogged){
        logindialog->show();
    }else{
        openfile->show();
    }

}

void Controller::errorConnection()
{

    QMessageBox::critical(this,"Error","Something went wrong!Please try again later.");
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
    //to updateButton in notepad
    emit updateButton(str,imagex);


    regDialog->close();
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
    //to update dialog
    emit userLogged(currentUser);
    userIsLogged=true;
    QImage imagex;
    imagex.loadFromData(currentUser.getImage());

    emit updateButton(currentUser.getName()+" "+currentUser.getSurname(),imagex);
    emit loginDialogClear();
    logindialog->close();
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
    this->close();
}

void Controller::notLogged()
{
    QMessageBox::warning(this,"Error", "Plese login");
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
    //socket.logoutMessage(currentUser)
    notepad->close();
    updateForm->close();
    confirmpwd->close();
    emit loginDialogClear();
    logindialog->show();
}
