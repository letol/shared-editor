#ifndef REGISTRATIONDIALOG_H
#define REGISTRATIONDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <user.h>

namespace Ui {
class RegistrationDialog;
}

class RegistrationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationDialog(QWidget *parent = nullptr);
    ~RegistrationDialog();

private slots:
    void on_pushButton_image_clicked();

    void on_pushButton_clicked();

private:
    Ui::RegistrationDialog *ui;
   // User *user;
};

#endif // REGISTRATIONDIALOG_H
