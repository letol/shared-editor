#include "openfiledialog.h"
#include "ui_openfiledialog.h"
#include <QDebug>

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
   emit openNewFile();
}
