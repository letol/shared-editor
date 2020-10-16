#ifndef OPENFILEDIALOG_H
#define OPENFILEDIALOG_H

#include <QDialog>
#include <QFileSystemModel>


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
    void openFile(const QString& path);
    void openNewFile();
private slots:

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::OpenFileDialog *ui;
    QFileSystemModel *fileModel;



};

#endif // OPENFILEDIALOG_H
