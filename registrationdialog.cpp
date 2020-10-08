#include "registrationdialog.h"
#include "ui_registrationdialog.h"
#include <QPixmap>
#include <QBuffer>
#include<QDebug>

RegistrationDialog::RegistrationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrationDialog)
{
    ui->setupUi(this);
    QImage image;
    image.load(":/images/profile.png");
    image = image.scaledToWidth(ui->lbl_image->width(), Qt::SmoothTransformation);
    image = image.scaledToHeight(ui->lbl_image->height(),Qt::SmoothTransformation);
    ui->lbl_image->setPixmap(QPixmap::fromImage(image));
    ui->pushButton->setEnabled(false);
    int size= sizeof (valid);
    for (int i =0;i<size ;i++ ) {
        valid[i]=false;

    }



}

RegistrationDialog::~RegistrationDialog()
{
    delete ui;
}

void RegistrationDialog::on_pushButton_image_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Choose"),"",tr("Images (*.png *.jpg)"));

    if(QString::compare(filename,QString())!=0){
        QImage image;
        bool valid = image.load(filename);
        if(valid){
            image = image.scaledToWidth(ui->lbl_image->width(), Qt::SmoothTransformation);
            image = image.scaledToHeight(ui->lbl_image->height(),Qt::SmoothTransformation);
            ui->lbl_image->setPixmap(QPixmap::fromImage(image));

        }
        else{
            ui->lbl_error->setText("Choose an other image");



        }
    }
}

void RegistrationDialog::on_pushButton_clicked()
{
    QString name = ui->lineEdit_name->text();
    QString surname = ui->lineEdit_surname->text();
    QString nickname = ui->lineEdit_nickname->text();
    QString email = ui->lineEdit_email->text();
    QString pwd = ui->lineEdit_password->text();
    QString pwdRepeat = ui->lineEdit_password->text();
    // Preparation of our QPixmap
    const QPixmap* pixmap = ui->lbl_image->pixmap();
    QByteArray bArray;
    QBuffer buffer(&bArray);
    buffer.open(QIODevice::WriteOnly);
    pixmap->save(&buffer, "PNG");


    User userMessage(nickname,name,surname,email,pwd,bArray);

    SocketClient s;
    s.setSocket();
    s.registrationMessage(userMessage);
    s.readyRead();





    //controllo nickname valido interroga server
    //capire come mandare user al server




}


void RegistrationDialog::on_lineEdit_name_textChanged(const QString &arg1)
{   //changes all of your whitespace characters to a single instance of ASCII 32,
    QString name = arg1.simplified();
    name.replace( " ", "" );
    if(name.isEmpty()){
            ui->lbl_error->setText("Name must be not empty");
            valid[0]=false;
        }
        else{
            ui->lbl_error->clear();
            valid[0]=true;
            checkValid(valid);
         }

}

void RegistrationDialog::on_lineEdit_surname_textChanged(const QString &arg1)
{
    QString sname = arg1.simplified();
    sname.replace( " ", "" );
    if(sname.isEmpty()){
        ui->lbl_error->setText("Surname must be not empty");
        valid[1]=false;
    }
    else{
        ui->lbl_error->clear();
        valid[1]=true;
        checkValid(valid);
     }
}

void RegistrationDialog::on_lineEdit_nickname_textChanged(const QString &arg1)
{
    QString str = arg1.simplified();
    str.replace( " ", "" );
    if(str.isEmpty()){
        ui->lbl_error->setText("Nickname must be not empty");
        valid[2]=false;
    }
    else{
        ui->lbl_error->clear();
        valid[2]=true;
        checkValid(valid);
     }

}

void RegistrationDialog::on_lineEdit_email_textChanged(const QString &arg1)
{
    QString str = arg1.simplified();
    str.replace( " ", "" );
    if(str.isEmpty() || !str.contains("@") || !str.contains(".")){
        ui->lbl_error->setText("Email is not valid");
        valid[3]=false;
    }
    else{
        ui->lbl_error->clear();
        valid[3]=true;
        checkValid(valid);
     }
}

void RegistrationDialog::on_lineEdit_password_textChanged(const QString &arg1)
{
    QString str = arg1.simplified();
    str.replace( " ", "" );
    QString regexp= "^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=.*[@#$%^&+=])(?=\\S+$).{8,}$";
    /*" Password must be:\n" +
            "     * At least 8 chars\n" +
            "     * Contains at least one digit\n" +
            "     * Contains at least one lower alpha char and one upper alpha char\n" +
            "     * Contains at least one char within a set of special chars (@#%$^ etc.)\n" +
            "     * Does not contain space, tab, etc.")*/


    if(str.isEmpty()){
        ui->lbl_error->setText("Password must be not empty");
        valid[4]=false;
    }
    else{
        ui->lbl_error->clear();
        valid[4]=true;
        checkValid(valid);
     }
    if(!str.contains(regexp)){
        ui->lbl_error->setText("Password must be at least 8 characters,\n"
                               "contain at least one number, at least one\n"
                               "capital letter and at least one lowercase\n"
                               "and one special character");
        valid[4]=false;
    }
    else{
        ui->lbl_error->clear();
        valid[4]=true;
        checkValid(valid);
     }
}

void RegistrationDialog::on_lineEdit_pwdrepeat_textChanged(const QString &arg1)
{
    QString str = arg1.simplified();
    str.replace( " ", "" );
    if(str.isEmpty()) {
        ui->lbl_error->setText("Password must be not empty");
        valid[5]=false;
    }
    else{
        ui->lbl_error->clear();
        valid[5]=true;
        checkValid(valid);
     }

    if(str.compare(ui->lineEdit_password->text())!=0){
        ui->lbl_error->setText("Passwords must match");
        valid[5]=false;

    }
    else{
        ui->lbl_error->clear();
        valid[5]=true;
        checkValid(valid);
     }
}

void RegistrationDialog::checkValid(bool* valid){

    int count=0;
    int size= sizeof (valid);
    for (int i =0;i<size  ;i++ ) {
        //qInfo()<<valid[i];
        if(valid[i]==true)
            count++;

    }
    if(count==6)
        ui->pushButton->setEnabled(true);
    else
        ui->pushButton->setEnabled(false);
    //qInfo()<<count;

}
