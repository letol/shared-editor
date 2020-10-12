#ifndef OPENFILEDIALOG_H
#define OPENFILEDIALOG_H

#include <QDialog>
#include <QFileSystemModel>
#include "notepad.h"

namespace Ui {
class OpenFileDialog;
}

class OpenFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenFileDialog(QWidget *parent = nullptr);
    ~OpenFileDialog();


signals:
    //void openFile();
private slots:

    void on_listView_doubleClicked(const QModelIndex &index);

private:
    Ui::OpenFileDialog *ui;
    QFileSystemModel *fileModel;


};

#endif // OPENFILEDIALOG_H
