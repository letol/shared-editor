#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if(username ==  "test" && password == "test") {
        Notepad *notepad = new Notepad(this);
        notepad->showMaximized();
    }
    else {
        QMessageBox::warning(this,"Login", "Username and password is not correct");
    }
}

void LoginDialog::on_pushButton_clicked()
{
    this->hide();
    RegistrationDialog *registration = new RegistrationDialog(this);
    registration->show();
}
