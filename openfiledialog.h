#ifndef OPENFILEDIALOG_H
#define OPENFILEDIALOG_H

#include <QDialog>
#include <QFileSystemModel>
#include <QStandardItem>
#include "documentmessage.h"


namespace Ui {
class OpenFileDialog;
}

class OpenFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenFileDialog(QWidget *parent = nullptr);
    ~OpenFileDialog();
    void setFileList(QVector<DocumentMessage>& docList);

signals:
    void openFile(const QUuid documentId);
    void openNewFile(const QString& name);

private slots:

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_nameFile_textChanged();

    void on_uri_textChanged();

    void on_uriPushButton_clicked();

private:
    Ui::OpenFileDialog *ui;
    QStandardItemModel *fileModel;
    QVector<DocumentMessage> files;

};

#endif // OPENFILEDIALOG_H
