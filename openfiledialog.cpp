#include "openfiledialog.h"
#include "ui_openfiledialog.h"
#include <QDebug>

OpenFileDialog::OpenFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenFileDialog)
{
    ui->setupUi(this);
    fileModel = new QStandardItemModel(0, 4, this);
    ui->listView->setModel(fileModel);
    //ui->listView->setViewMode(QListView::IconMode);

}

OpenFileDialog::~OpenFileDialog()
{
    delete ui;
}

void OpenFileDialog::setFileList(QVector<DocumentMessage>& docList)
{
    files = docList;
    qDebug() << "File list:";
    for (int row = 0; row < docList.size(); ++row) {
        QStandardItem *nameItem = new QStandardItem(docList[row].getName());
        QStandardItem *documentIdItem = new QStandardItem(docList[row].getDocumentId().toString());
        QStandardItem *ownerEmailItem = new QStandardItem(docList[row].getOwnerEmail());
        QStandardItem *dateItem = new QStandardItem(docList[row].getDate());

        fileModel->setItem(row, 0, nameItem);
        fileModel->setItem(row, 1, documentIdItem);
        fileModel->setItem(row, 2, ownerEmailItem);
        fileModel->setItem(row, 3, dateItem);

        qDebug() << docList[row].getDocumentId();
    }
}

void OpenFileDialog::on_listView_doubleClicked(const QModelIndex &index)
{
    DocumentMessage selected = files[index.row()];
    emit openFile(selected.getDocumentId());
    this->hide();
}

void OpenFileDialog::on_pushButton_clicked()
{
   this->hide();
   emit openNewFile();
}
