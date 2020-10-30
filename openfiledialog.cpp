#include "openfiledialog.h"
#include "ui_openfiledialog.h"
#include <QDebug>
#include <QRegularExpressionValidator>

OpenFileDialog::OpenFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenFileDialog)
{
    ui->setupUi(this);
    fileModel = new QFileSystemModel(this);
    QString sPath = "";//"C:\\Users\\Raluca\\Desktop";//TODO server
    fileModel->setRootPath(sPath);



    //fileModel->setFilter(QDir::Readable | QDir::Writable);
    //todo capire come ingrandire le icon
     ui->listView->setModel(fileModel);

     QModelIndex idx = fileModel->index(fileModel->rootPath());
     ui->listView->setRootIndex(idx);
     ui->listView->setViewMode(QListView::IconMode);

    QRegularExpression rxString("^(?!\\s*$).+.",QRegularExpression::CaseInsensitiveOption);
     ui->nameFile->setValidator(new QRegularExpressionValidator(rxString, this));
     ui->uri->setValidator(new QRegularExpressionValidator(rxString, this));
     ui->newFilePushButton->setEnabled(false);
     ui->uriPushButton->setEnabled(false);


}

OpenFileDialog::~OpenFileDialog()
{
    delete ui;
}



void OpenFileDialog::on_listView_doubleClicked(const QModelIndex &index)
{   QString path = fileModel->fileInfo(index).absoluteFilePath();

    if(fileModel->fileInfo(index).isDir()){
        ui->listView->setRootIndex(fileModel->setRootPath(path));
    }if(fileModel->fileInfo(index).isFile()){
        emit openFile(path);
        this->hide();
    }


}

void OpenFileDialog::on_pushButton_clicked()
{
   this->hide();
   emit openNewFile(ui->nameFile->text());
}

void OpenFileDialog::on_nameFile_textChanged()
{
    if(ui->nameFile->hasAcceptableInput())
        ui->newFilePushButton->setEnabled(true);
    else
        ui->newFilePushButton->setEnabled(false);
}

void OpenFileDialog::on_uri_textChanged()
{
    if(ui->uri->hasAcceptableInput())
        ui->uriPushButton->setEnabled(true);
    else
       ui->uriPushButton->setEnabled(false);
}

void OpenFileDialog::on_uriPushButton_clicked()
{
    //send uri to scocket
    //ui->uri->text()
}
