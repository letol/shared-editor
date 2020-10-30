#ifndef OPENFILEDIALOG_H
#define OPENFILEDIALOG_H

#include <QDialog>
#include <QFileSystemModel>
#include <QStandardItem>
#include <QUrl>
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
    void openFile(const QUrl uri);
    void openNewFile(const QString& name);

private slots:

    void on_newFilePushButton_clicked();

    void on_nameFile_textChanged();

    void on_uri_textChanged();

    void on_uriPushButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::OpenFileDialog *ui;
    QStandardItemModel *fileModel;
    QPushButton* uriButton;
    QVector<DocumentMessage> files;

};

#endif // OPENFILEDIALOG_H
