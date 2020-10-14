#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{

    socket.setSocket();
    ui->setupUi(this);

    connect(&socket,&SocketClient::registrationOK,this,&LoginDialog::regOK);
    connect(&socket,&SocketClient::registrationKO,this,&LoginDialog::regKO);
    connect(&socket,&SocketClient::loginOK,this,&LoginDialog::logOK);
    connect(&socket,&SocketClient::loginKO,this,&LoginDialog::logKO);
    connect(&socket,&SocketClient::errorDB,this,&LoginDialog::errorDB);

}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    User userlogin(username,password);
    socket.loginMessage(userlogin);

}

void LoginDialog::on_pushButton_clicked()
{
    this->hide();
    RegistrationDialog *registration = new RegistrationDialog(this);
    registration->show();
}

void LoginDialog::receveRegistrationData(const User &user)
{
    socket.registrationMessage(user);
}

void LoginDialog::regOK()
{


    //Notepad *notepad = new Notepad();
    //notepad->showMaximized();
    OpenFileDialog *openfile= new OpenFileDialog(this);
    openfile->show();
    emit closeRegDialog();


}

void LoginDialog::regKO()
{
    emit messageRegDialog("Email or nickname are already used");
}

void LoginDialog::logOK()
{
    this->hide();
    OpenFileDialog *openfile= new OpenFileDialog(this);
    openfile->show();
    //Notepad *notepad = new Notepad();
    //notepad->showMaximized();
     emit loggedUser(loginUser);

}

void LoginDialog::logKO()
{
  QMessageBox::warning(this,"Login", "Username and password are not valid");

}

void LoginDialog::errorDB()
{
    QMessageBox::warning(this,"Error", "Something went wrong!Please try again later.");
    this->close();
}

void LoginDialog::showDialog()
{
    this->show();
}
