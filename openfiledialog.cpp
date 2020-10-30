#include "openfiledialog.h"
#include "ui_openfiledialog.h"
#include <QDebug>
#include <QMessageBox>
#include <QRegularExpressionValidator>

OpenFileDialog::OpenFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenFileDialog)
{
    ui->setupUi(this);
    ui->tableView->setShowGrid(false);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSelectionBehavior(QTableView::SelectRows);
    fileModel = new QStandardItemModel(0, 2, this);

    fileModel->setHorizontalHeaderLabels({"Name","Date"});
    ui->tableView->setModel(fileModel);
    ui->tableView->setColumnWidth(0,ui->tableView->width()/2);
    ui->tableView->setColumnWidth(1,ui->tableView->width()/2);



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

void OpenFileDialog::setFileList(QVector<DocumentMessage>& docList)
{
    files = docList;
    qDebug() << "File list:";
    /*for (int row = 0; row < docList.size(); ++row) {
        QStandardItem *nameItem = new QStandardItem(docList[row].getName());
        QStandardItem *documentIdItem = new QStandardItem(docList[row].getDocumentId().toString());
        QStandardItem *ownerEmailItem = new QStandardItem(docList[row].getOwnerEmail());
        QStandardItem *dateItem = new QStandardItem(docList[row].getDate());



        qDebug() << docList[row].getDocumentId();
    }*/
    for (int row = 0; row < 5; ++row) {


        QStandardItem *nameItem = new QStandardItem("Prova");
        nameItem->setEditable(false);
        nameItem->setTextAlignment(Qt::AlignCenter);
        QStandardItem *dateItem = new QStandardItem("30/10/20");
        dateItem->setEditable(false);
        dateItem->setTextAlignment(Qt::AlignCenter);
        fileModel->appendRow({nameItem,dateItem});






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

void OpenFileDialog::on_tableView_doubleClicked(const QModelIndex &index)
{
    //DocumentMessage selected = files[index.row()];
    //emit openFile(selected.getDocumentId());
    //this->hide();
    qInfo()<<index;
}

void OpenFileDialog::copyUri()
{
    //copia
}
