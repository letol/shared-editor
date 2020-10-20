#include "updateformdialog.h"
#include "ui_updateformdialog.h"
#include <QFileDialog>
#include <QRegularExpressionValidator>
#include <QMessageBox>

UpdateFormDialog::UpdateFormDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateFormDialog)
{
    ui->setupUi(this);

    cp = new ConfirmPassword(this);

    lineName= new QLineEdit(this);
    lineSurname= new QLineEdit(this);
    lineName->hide();
    lineSurname->hide();
    QRegularExpression rxString("^(?!\\s*$).+.",QRegularExpression::CaseInsensitiveOption);
    lineName->setValidator(new QRegularExpressionValidator(rxString, this));
    lineSurname->setValidator(new QRegularExpressionValidator(rxString, this));

    connect(lineName,&QLineEdit::returnPressed,this,&UpdateFormDialog::changeName);
    connect(lineSurname,&QLineEdit::returnPressed,this,&UpdateFormDialog::changeCognome);
    connect(this,SIGNAL(pwdChange(QString,QString)),parent,SLOT(pwdChanged(QString,QString)));
    connect(this,SIGNAL(nameChange(QString)),parent,SLOT(nameChanged(QString)));
    connect(this,SIGNAL(surnameChange(QString)),parent,SLOT(surnameChanged(QString)));
    connect(this,SIGNAL(imageChange(QByteArray)),parent,SLOT(imageChanged(QByteArray)));

    connect(parent,SIGNAL(userIsChanged(User)),this,SLOT(updateOK(User)));
    connect(parent,SIGNAL(udpKO(QString)),this,SLOT(updateKO(QString)));
    connect(parent,SIGNAL(pwdKO(QString)),this,SLOT(pwdError(QString)));
    connect(parent,SIGNAL(userLogged(User)),this,SLOT(userLogged(User)));
}

UpdateFormDialog::~UpdateFormDialog()
{
    delete ui;
}

void UpdateFormDialog::updateOK(const User &user)
{
   User userChange=user;
   ui->error->clear();
   /* QImage image;
    image.loadFromData(userChange.getImage());
    image = image.scaledToWidth(ui->image->width(), Qt::SmoothTransformation);
    image = image.scaledToHeight(ui->image->height(),Qt::SmoothTransformation);
    ui->image->setPixmap(QPixmap::fromImage(image));*/



}

void UpdateFormDialog::updateKO(const QString &str)
{
    ui->error->setText(str);
    ui->name->setText(user.getName());
    ui->surmane->setText(user.getSurname());
}

void UpdateFormDialog::pwdError(const QString &str)
{
    QMessageBox::warning(this,"Error password", str);
}

void UpdateFormDialog::userLogged(const User &userL)
{
    user=userL;
    QPixmap pixmap;
    qInfo()<<"Image size:"<< user.getImage().size();

    QImage image;
    if(image.loadFromData(user.getImage()))
    {
        qInfo()<< image.size();
        image = image.scaledToWidth(ui->image->width(), Qt::SmoothTransformation);
        image = image.scaledToHeight(ui->image->height(),Qt::SmoothTransformation);
        ui->image->setPixmap(QPixmap::fromImage(image));
        ui->image->show();
    }

    ui->surmane->setText(user.getSurname());
    ui->name->setText(user.getName());


}


void UpdateFormDialog::on_imageChange_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Choose"),"",tr("Images (*.png *.jpg)"));

           if(QString::compare(filename,QString())!=0){
               QImage image;
               bool check = image.load(filename);
               if(check){
                   image = image.scaledToWidth(ui->image->width(), Qt::SmoothTransformation);
                   image = image.scaledToHeight(ui->image->height(),Qt::SmoothTransformation);
                   ui->image->setPixmap(QPixmap::fromImage(image));
                   QByteArray arr = QByteArray::fromRawData((const char*)image.bits(), image.sizeInBytes());
                   emit imageChange(arr);
                   ui->error->clear();


               }
               else{
                  ui->error->setText("Choose an other image");



               }
           }
}

void UpdateFormDialog::on_passwordChange_clicked()
{
    cp->show();
}

void UpdateFormDialog::on_nameChange_clicked()
{
    QRect pos = ui->name->geometry();
    ui->name->hide();
    lineName->setGeometry(pos);
    lineName->setText(ui->name->text());
    lineName->show();

}

void UpdateFormDialog::on_surnameChange_clicked()
{
   QRect pos =ui->surmane->geometry();
   ui->surmane->hide();
   lineSurname->setGeometry(pos);
   lineSurname->setText(ui->surmane->text());
   lineSurname->show();
}

void UpdateFormDialog::changeName()
{
    if(lineName->hasAcceptableInput()){
        emit nameChange(lineName->text());
        ui->name->setText(lineName->text());
        lineName->hide();
        ui->name->show();
       }

}

void UpdateFormDialog::changeCognome()
{
    if(lineSurname->hasAcceptableInput()){

        emit surnameChange(lineSurname->text());
        ui->surmane->setText(lineSurname->text());
        lineSurname->hide();
        ui->surmane->show();
    }
}

void UpdateFormDialog::pwdData(const QString &pwd, const QString &pwdr)
{
    emit pwdChange(pwd,pwdr);

}
