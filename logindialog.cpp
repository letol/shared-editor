#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include "notepad.h"
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{


    ui->setupUi(this);

    registration = new RegistrationDialog(this);
    registration->setModal(Qt::ApplicationModal);

    connect(this,SIGNAL(loginData(User)),parent,SLOT(loginData(User)));
    connect(parent,SIGNAL(errorLogin(QString)),this,SLOT(logKO(QString)));
    connect(this,SIGNAL(registrationData(User)),parent,SLOT(regData(User)));
    connect(parent,SIGNAL(regClose()),this,SLOT(regOK()));
    connect(parent,SIGNAL(errorReg(QString)),this,SLOT(regKO(QString)));




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
    emit loginData(userlogin);



}

void LoginDialog::on_pushButton_clicked()
{
    this->hide();
    registration->show();
}

void LoginDialog::receveRegistrationData(const User &user)
{
    emit registrationData(user);
}

void LoginDialog::regOK()
{
    registration->close();
}

void LoginDialog::regKO(const QString& str)
{
    emit messageRegDialog(str);
}



void LoginDialog::logKO(const QString& str)
{
  QMessageBox::warning(this,"Erorr Login", str);

}


void LoginDialog::showDialog()
{
    this->show();
}
