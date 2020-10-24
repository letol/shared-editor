#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QRegularExpressionValidator>
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{


    ui->setupUi(this);
    ui->pushButton_login->setEnabled(false);
    QRegularExpression rxString("^(?!\\s*$).+.",QRegularExpression::CaseInsensitiveOption);
    ui->lineEdit_password->setValidator(new QRegularExpressionValidator(rxString, this));
    ui->lineEdit_username->setValidator(new QRegularExpressionValidator(rxString, this));

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
    emit clickSignIn();

}


void LoginDialog::logKO(const QString& str)
{
  QMessageBox::warning(this,"Erorr Login", str);

}



void LoginDialog::on_lineEdit_username_textChanged()
{
    if(ui->lineEdit_password->hasAcceptableInput()&&ui->lineEdit_username->hasAcceptableInput())
        ui->pushButton_login->setEnabled(true);
    else
        ui->pushButton_login->setEnabled(false);
}

void LoginDialog::on_lineEdit_password_textChanged()
{
    if(ui->lineEdit_password->hasAcceptableInput()&&ui->lineEdit_username->hasAcceptableInput())
        ui->pushButton_login->setEnabled(true);
    else
        ui->pushButton_login->setEnabled(false);

}

void LoginDialog::clean()
{
    ui->lineEdit_password->clear();
    ui->lineEdit_username->clear();

}
