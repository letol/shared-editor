#include "registrationdialog.h"
#include "ui_registrationdialog.h"
#include <QPixmap>
#include <QBuffer>
#include <QDebug>
#include <QRegExpValidator>


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
    QRegularExpression rx("^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=.*[@#$%^&+=])(?=\\S+$).{8,}$");
    ui->lineEdit_password->setValidator(new QRegularExpressionValidator(rx, this));

    QRegularExpression rxemail("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b",
                              QRegularExpression::CaseInsensitiveOption);
    ui->lineEdit_email->setValidator(new QRegularExpressionValidator(rxemail, this));
    QRegularExpression rxString("^(?!\\s*$).+.",QRegularExpression::CaseInsensitiveOption);
    ui->lineEdit_name->setValidator(new QRegularExpressionValidator(rxString, this));
    ui->lineEdit_surname->setValidator(new QRegularExpressionValidator(rxString, this));
    ui->lineEdit_nickname->setValidator(new QRegularExpressionValidator(rxString, this));
}

RegistrationDialog::~RegistrationDialog()
{
    delete ui;
}

void RegistrationDialog::on_pushButton_image_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Choose"),"",tr("Images (*.png *.jpg *.jpeg)"));

    if(QString::compare(filename,QString())!=0){
        QImage image;
        bool check = image.load(filename);
        const char* typeImage = std::move(filename.split(".")[1].toUpper().toStdString().c_str());

        if(check){
            image = image.scaledToWidth(ui->lbl_image->width(), Qt::SmoothTransformation);
            image = image.scaledToHeight(ui->lbl_image->height(),Qt::SmoothTransformation);
            ui->lbl_image->setPixmap(QPixmap::fromImage(image));
            QByteArray byteArray;
            QBuffer buffer(&byteArray);
            image.save(&buffer, typeImage);
            user.setImage(byteArray);
            ui->lbl_error->clear();


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
    pwd.replace(" ","");
    QString pwdRepeat = ui->lineEdit_password->text();
    QByteArray byteArray = user.getImage();
    user=User(nickname,name,surname,email,pwd,byteArray);

    emit registratationData(user);

}


void RegistrationDialog::on_lineEdit_name_textChanged()
{  if(!ui->lineEdit_name->hasAcceptableInput()){
        ui->lbl_error->setText("Name must be not empty");
        valid["name"]=false;
    }
    else{
         ui->lbl_error->clear();
        valid["name"]=true;
        checkValid(valid);
    }
}

void RegistrationDialog::on_lineEdit_surname_textChanged()
{
    if(!ui->lineEdit_surname->hasAcceptableInput()){
        ui->lbl_error->setText("Surname must be not empty");
        valid["surname"]=false;
    }
    else{
        ui->lbl_error->clear();
        valid["surname"]=true;
        checkValid(valid);
    }
}

void RegistrationDialog::on_lineEdit_nickname_textChanged()
{
    if(!ui->lineEdit_nickname->hasAcceptableInput()){
         ui->lbl_error->setText("Nickname must be not empty");
         valid["nickname"]=false;
    }
    else{
        ui->lbl_error->clear();
        valid["nickname"]=true;
        checkValid(valid);
    }
}

void RegistrationDialog::on_lineEdit_email_textChanged()
{
    if(!ui->lineEdit_email->hasAcceptableInput()){
        ui->lbl_error->setText("Email is not valid");
        valid["email"]=false;
        }
        else{
        ui->lbl_error->clear();
            valid["email"]=true;
            checkValid(valid);
        }

}

void RegistrationDialog::on_lineEdit_password_textChanged(const QString &arg1)
{ QString str = arg1.simplified();
    if(!ui->lineEdit_password->hasAcceptableInput()){
        ui->lbl_error->setText("Password must be at least 8 characters,\n"
                               "contain at least one number, at least one\n"
                               "capital letter and at least one lowercase\n"
                               "and one special character");
        valid["pwd"]=false;
    }
    else{
        ui->lbl_error->clear();
        valid["pwd"]=true;
        checkValid(valid);
        if(str.compare(ui->lineEdit_pwdrepeat->text())!=0){
            ui->lbl_error->setText("Passwords must match");
            valid["pwdR"]=false;

        }
        else{
            ui->lbl_error->clear();
            valid["pwdR"]=true;
            checkValid(valid);
         }
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

void RegistrationDialog::on_lineEdit_pwdrepeat_textChanged(const QString &arg1)
{
    QString str = arg1.simplified();


    if(str.compare(ui->lineEdit_password->text())!=0){
        ui->lbl_error->setText("Passwords must match");
        valid["pwdR"]=false;

    }
    else{
        ui->lbl_error->clear();
        valid["pwdR"]=true;
        checkValid(valid);
     }
}

void RegistrationDialog::errorHeadling(const QString &str)
{
    ui->lbl_error->setText(str);
}


void RegistrationDialog::checkValid(QMap<QString,bool> valid){
   if(valid["name"]&&valid["surname"]&&valid["nickname"]
           &&valid["email"]&&valid["pwd"]&&valid["pwdR"]){
       ui->pushButton->setEnabled(true);

   }else{
       ui->pushButton->setEnabled(false);
       //qInfo()<<valid["name"]<<valid["surname"]<<valid["nickname"]<<valid["email"]<<valid["pwd"]<<valid["pwdR"];

   }

}



void RegistrationDialog::on_login_pushButton_clicked()
{
    this->hide();
    this->clean();
    emit openLogin();
}

void RegistrationDialog::clean()
{
    QImage image;
    image.load(":/images/profile.png");
    image = image.scaledToWidth(ui->lbl_image->width(), Qt::SmoothTransformation);
    image = image.scaledToHeight(ui->lbl_image->height(),Qt::SmoothTransformation);
    ui->lbl_image->setPixmap(QPixmap::fromImage(image));
    ui->lbl_error->clear();
    ui->lineEdit_name->clear();
    ui->lineEdit_surname->clear();
    ui->lineEdit_email->clear();
    ui->lineEdit_password->clear();
    ui->lineEdit_pwdrepeat->clear();
    ui->lineEdit_nickname->clear();

}
