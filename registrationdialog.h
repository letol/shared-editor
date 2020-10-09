#ifndef REGISTRATIONDIALOG_H
#define REGISTRATIONDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include "user.h"


namespace Ui {
class RegistrationDialog;
}

class RegistrationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationDialog(QWidget *parent = nullptr);
    ~RegistrationDialog();

signals:
    void registratationData(const User &user);

private slots:
    void on_pushButton_image_clicked();
    void on_pushButton_clicked();
    void on_lineEdit_name_textChanged(const QString &arg1);

    void on_lineEdit_surname_textChanged(const QString &arg1);

    void on_lineEdit_nickname_textChanged(const QString &arg1);

    void on_lineEdit_email_textChanged(const QString &arg1);

    void on_lineEdit_password_textChanged(const QString &arg1);

    void on_lineEdit_pwdrepeat_textChanged(const QString &arg1);

private:
    Ui::RegistrationDialog *ui;

    bool valid[6];//six fields form registration

    void checkValid(bool* valid);

};

#endif // REGISTRATIONDIALOG_H
