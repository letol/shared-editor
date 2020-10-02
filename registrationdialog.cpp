#include "registrationdialog.h"
#include "ui_registrationdialog.h"
#include <QMessageBox>

RegistrationDialog::RegistrationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrationDialog)
{
    ui->setupUi(this);
}

RegistrationDialog::~RegistrationDialog()
{
    delete ui;
}


void RegistrationDialog::on_pushButton_login_clicked()
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
