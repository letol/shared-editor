#include "updateform.h"
#include "ui_updateform.h"

#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionValidator>


UpdateForm::UpdateForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UpdateForm)
{

    ui->setupUi(this);
    QImage image;
    image.load(":/images/profile.png");
    image = image.scaledToWidth(ui->lb_image->width(), Qt::SmoothTransformation);
    image = image.scaledToHeight(ui->lb_image->height(),Qt::SmoothTransformation);
    ui->lb_image->setPixmap(QPixmap::fromImage(image));

    //TODO popola lbl from server
    //setta nome e cognome sul push button
    lineNome= new QLineEdit(this);
    lineCognome= new QLineEdit(this);
    lineNome->hide();
    lineCognome->hide();
    QRegularExpression rxString("^(?!\\s*$).+.",QRegularExpression::CaseInsensitiveOption);
    lineNome->setValidator(new QRegularExpressionValidator(rxString, this));
    lineCognome->setValidator(new QRegularExpressionValidator(rxString, this));

    connect(lineNome,&QLineEdit::returnPressed,this,&UpdateForm::changeName);
    connect(lineCognome,&QLineEdit::returnPressed,this,&UpdateForm::changeCognome);


}

UpdateForm::~UpdateForm()
{
    delete ui;
}

void UpdateForm::on_pushButto_nome_clicked()
{
    QRect pos = ui->lbl_nome->geometry();
    ui->lbl_nome->hide();
    lineNome->setGeometry(pos);
    lineNome->setText(ui->lbl_nome->text());
    lineNome->show();


}

void UpdateForm::changeName()
{
    if(lineNome->hasAcceptableInput()){
        ui->lbl_nome->setText(lineNome->text());
        lineNome->hide();
        ui->lbl_nome->show();
        //send to server aspetta conferma
    }


}

void UpdateForm::changeCognome()
{
    if(lineCognome->hasAcceptableInput()){
        ui->lbl_error->clear();
        ui->lbl_cognome->setText(lineCognome->text());
        lineCognome->hide();
        ui->lbl_cognome->show();
        //send to server aspetta conferma
    }

}

void UpdateForm::on_pushButton_cognome_clicked()
{
    QRect pos =ui->lbl_cognome->geometry();
    ui->lbl_cognome->hide();
    lineCognome->setGeometry(pos);
    lineCognome->setText(ui->lbl_cognome->text());
    lineCognome->show();

}

void UpdateForm::on_pushButton_image_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Choose"),"",tr("Images (*.png *.jpg)"));

    if(QString::compare(filename,QString())!=0){
        QImage image;
        bool check = image.load(filename);
        if(check){
            image = image.scaledToWidth(ui->lb_image->width(), Qt::SmoothTransformation);
            image = image.scaledToHeight(ui->lb_image->height(),Qt::SmoothTransformation);
            ui->lb_image->setPixmap(QPixmap::fromImage(image));
            ui->lbl_error->clear();


        }
        else{
            ui->lbl_error->setText("Choose an other image");



        }
    }
}

void UpdateForm::on_button_password_clicked()
{

    ConfirmPassword *cp = new ConfirmPassword(this);
    cp->show();
}


