#ifndef OPENFILEDIALOG_H
#define OPENFILEDIALOG_H

#include <QDialog>
#include <QFileSystemModel>
#include <QStandardItem>
#include <QUrl>
#include <QItemSelection>
#include <QMouseEvent>
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

    void clean();

signals:
    void openFile(const QUrl uri);
    void openNewFile(const QString& name);
    void deleteFile(const DocumentMessage& docMessage);
protected:
   void mouseReleaseEvent(QMouseEvent * event) override;

private slots:

    void on_newFilePushButton_clicked();

    void on_nameFile_textChanged();

    void on_uri_textChanged();

    void on_uriPushButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_removePushButton_clicked();

    void selectedRow(const QItemSelection & selected, const QItemSelection & deselected);


private:
    Ui::OpenFileDialog *ui;
    QStandardItemModel *fileModel;
    QPushButton* uriButton;
    QVector<DocumentMessage> files;
    DocumentMessage selectedFile;

};

#endif // OPENFILEDIALOG_H
