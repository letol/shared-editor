#include "updateform.h"
#include "ui_updateform.h"

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


}

UpdateForm::~UpdateForm()
{
    delete ui;
}
