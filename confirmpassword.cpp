#include "confirmpassword.h"
#include "ui_confirmpassword.h"
#include "QRegularExpressionValidator"
#include <QDebug>

ConfirmPassword::ConfirmPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmPassword)
{
    ui->setupUi(this);

    QRegularExpression rx("^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=.*[@#$%^&+=])(?=\\S+$).{8,}$");
    ui->new_password->setValidator(new QRegularExpressionValidator(rx, this));


}

ConfirmPassword::~ConfirmPassword()
{
    delete ui;
}

void ConfirmPassword::on_new_password_textChanged(const QString &arg1)
{
    QString str = arg1.simplified();
        if(!ui->new_password->hasAcceptableInput()){
            ui->error->setText("Password must be at least 8 characters,\n"
                                   "contain at least one number, at least one\n"
                                   "capital letter and at least one lowercase\n"
                                   "and one special character");
            valid["pwd"]=false;
        }
        else{
            ui->error->clear();
            valid["pwd"]=true;
            checkValid(valid);
        }

        if(str.compare(ui->new_rpwd->text())!=0){
            ui->error->setText("Passwords must match");
            valid["pwdR"]=false;

        }
        else{
            ui->error->clear();
            valid["pwdR"]=true;
            checkValid(valid);
         }
       /*

        " Password must be:\n" +
                "     * At least 8 chars\n" +
                "     * Contains at least one digit\n" +
                "     * Contains at least one lower alpha char and one upper alpha char\n" +
                "     * Contains at least one char within a set of special chars (@#%$^ etc.)\n" +
                "     * Does not contain space, tab, etc.")

    */

}

void ConfirmPassword::on_new_rpwd_textChanged(const QString &arg1)
{
    QString str = arg1.simplified();


    if(str.compare(ui->password->text())!=0){
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
        //manda al server

    }else{


    }

}


void ConfirmPassword::on_pushButton_cancel_clicked()
{
    this->close();
}

void ConfirmPassword::on_pushButton_ok_clicked()
{

}
