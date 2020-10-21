#include "confirmpassword.h"
#include "ui_confirmpassword.h"
#include "QRegularExpressionValidator"
#include <QDebug>
#include <QMessageBox>
ConfirmPassword::ConfirmPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmPassword)
{
    ui->setupUi(this);
    ui->pushButton_ok->setEnabled(false);
    QRegularExpression rx("^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=.*[@#$%^&+=])(?=\\S+$).{8,}$");
    ui->new_password->setValidator(new QRegularExpressionValidator(rx, this));
    ui->password->setCursor(QCursor());
    connect(this,SIGNAL(passwordData(QString,QString)),parent,SLOT(pwdData(QString,QString)));
    connect(parent,SIGNAL(pwdKO(QString)),this,SLOT(errorPwd(QString)));
    connect(parent,SIGNAL(pwdOK()),this,SLOT(updOK()));

}

ConfirmPassword::~ConfirmPassword()
{
    delete ui;
}

void ConfirmPassword::errorPwd(const QString& str)
{
   QMessageBox::warning(this,"Error password", str);

}

void ConfirmPassword::updOK()
{
    QMessageBox::information(this,"Success","Password was upadte");
    this->close();
    this->ui->new_password->clear();
    this->ui->password->clear();
    this->ui->new_rpwd->clear();
    ui->error->clear();
}

void ConfirmPassword::on_new_password_textChanged(const QString &arg1)
{
    QString str = arg1.simplified();
        if(!ui->new_password->hasAcceptableInput()){
            ui->error->setText("Password must be at least 8 characters,contain at\n"
                               "least one number, at least one capital letter and\n"
                               "at least one lowercase and one special character");
            valid["pwd"]=false;
        }
        else{
            ui->error->clear();
            valid["pwd"]=true;
            checkValid(valid);
            if(str.compare(ui->new_rpwd->text())!=0){
                ui->error->setText("Passwords must match");
                valid["pwdR"]=false;

            }
            else{
                ui->error->clear();
                valid["pwdR"]=true;
                checkValid(valid);
             }
        }



}

void ConfirmPassword::on_new_rpwd_textChanged(const QString &arg1)
{
    QString str = arg1.simplified();


    if(str.compare(ui->new_password->text())!=0){
        ui->error->setText("Passwords must match");
        valid["pwdR"]=false;

    }
    else{
        ui->error->clear();
        valid["pwdR"]=true;
        checkValid(valid);
    }
}



void ConfirmPassword::checkValid(QMap<QString, bool> valid)
{
    if(valid["pwd"]&&valid["pwdR"]){
         ui->pushButton_ok->setEnabled(true);

    }else{
         ui->pushButton_ok->setEnabled(false);

    }

}


void ConfirmPassword::on_pushButton_cancel_clicked()
{
    this->close();
    this->ui->new_password->clear();
    this->ui->password->clear();
    this->ui->new_rpwd->clear();
}

void ConfirmPassword::on_pushButton_ok_clicked()
{

    const QString pwd = ui->password->text();
    const QString pwdNew= ui->new_password->text();
    emit passwordData(pwd,pwdNew);

}
