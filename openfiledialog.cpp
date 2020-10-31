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

    connect(
      ui->tableView->selectionModel(),
      SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
      SLOT(selectedRow(const QItemSelection &, const QItemSelection &))
     );



    QRegularExpression rxString("^(?!\\s*$).+.",QRegularExpression::CaseInsensitiveOption);
    ui->nameFile->setValidator(new QRegularExpressionValidator(rxString, this));
    ui->uri->setValidator(new QRegularExpressionValidator(rxString, this));
    ui->newFilePushButton->setEnabled(false);
    ui->uriPushButton->setEnabled(false);
    ui->removePushButton->setEnabled(false);




}

OpenFileDialog::~OpenFileDialog()
{
    delete ui;
}

void OpenFileDialog::setFileList(QVector<DocumentMessage>& docList)
{
    files = docList;
    qDebug() << "File list:";
    //clear table
    fileModel->setRowCount(0);


    for (int row = 0; row < docList.size(); ++row) {
        QStandardItem *nameItem = new QStandardItem(docList[row].getName());
        nameItem->setEditable(false);
        nameItem->setTextAlignment(Qt::AlignCenter);
        QStandardItem *dateItem = new QStandardItem(docList[row].getDate());
        dateItem->setEditable(false);
        dateItem->setTextAlignment(Qt::AlignCenter);
        fileModel->appendRow({nameItem,dateItem});



        qDebug() << docList[row].getDocumentId();
    }
}

void OpenFileDialog::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::LeftButton)
        qDebug() << "Only left button";
}

void OpenFileDialog::clean()
{   ui->tableView->selectionModel()->clearSelection();
    ui->nameFile->clear();
    ui->uri->clear();
}

void OpenFileDialog::on_newFilePushButton_clicked()
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
    emit openFile(ui->uri->text());
    this->hide();
}

void OpenFileDialog::on_tableView_doubleClicked(const QModelIndex &index)
{
    DocumentMessage selected = files[index.row()];
    QUrl uri;
    uri.setScheme("shared-editor");
    uri.setHost(selected.getDocumentId().toString(QUuid::WithoutBraces));
    emit openFile(uri);
    ui->tableView->selectionModel()->clearSelection();
    this->hide();
}



void OpenFileDialog::on_removePushButton_clicked()
{
    ui->tableView->selectionModel()->clearSelection();
}

void OpenFileDialog::selectedRow(const QItemSelection & selected, const QItemSelection & deselected)
{
    if(selected.isEmpty()){
        ui->removePushButton->setEnabled(false);
    }else{
        ui->removePushButton->setEnabled(true);
        DocumentMessage selectedFile = files[selected.indexes()[0].row()];
        qInfo()<<selectedFile.getDocumentId();
    }


}

