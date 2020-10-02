#include "registrationdialog.h"
#include "ui_registrationdialog.h"
#include <QPixmap>

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
    //QImage image = ui->lbl_image; convertire pixmap in image
    //todo controllo sulla lungezza di tutti i campi
    //controllo email
    //controllo nickname valido
    //capire come mandare user al server

    //if(QString::compare(pwd,pwdRepeat)!=0){

        ui->lbl_error->setText("Passwords must match");
        //ui->lbl_error->setStyleSheet("QLabel {color : red; }");
    //}
}
